#include "memory.cpp"
#define CACHE_DELAY_DEFAULT 2
class Cache {
   public:
    int cache_delay_timer;
    bool cache_in_use;
    int cur_caller_id = -1;
    Memory* main_mem;
    // Memory * to main_mem
    // 4 tag + 4 index + 2 offset bits + dirty + valid
    uint32_t cache[16][8];

    Cache(Memory* main_mem) {
        cache_delay_timer = CACHE_DELAY_DEFAULT;
        cache_in_use = false;
        cur_caller_id = -1;
        this->main_mem = main_mem;
    }

    uint32_t handle_cache_miss(uint32_t addr, uint32_t tag, uint32_t index,
                               uint32_t offset, int whois_calling) {
        // on cache miss, we need to:
        // fetch the line we want from memory
        uint32_t* fetched_line =
            this->main_mem->fetch(addr / WORDS_PER_LINE, whois_calling);
        if (fetched_line == nullptr) {
            return 0;
        }
        // find row in cache to evict
        // this should be trivial because it's just replace at current index
        uint32_t* line = nullptr;
        for (int i = 0; i < 16; i++) {
            if (cache[i][1] == tag) {
                line = cache[i];
            }
        }

        // if dirty, evict line by writing to main mem
        if (line[6]) {
            uint32_t addr_to_write_to = tag;
            addr_to_write_to = addr_to_write_to << 4;
            addr_to_write_to += index;
            addr_to_write_to = addr_to_write_to << 2;
            std::cout << addr_to_write_to << std::endl;

            this->main_mem->store_cache_ver(addr_to_write_to, line[2]);
            this->main_mem->store_cache_ver(addr_to_write_to + 1, line[3]);
            this->main_mem->store_cache_ver(addr_to_write_to + 2, line[4]);
            this->main_mem->store_cache_ver(addr_to_write_to + 3, line[5]);
        }
        // load in new data with appropriate tag/index/offset
        line[0] = tag;
        line[1] = index;
        line[2] = fetched_line[0];
        line[3] = fetched_line[1];
        line[4] = fetched_line[2];
        line[5] = fetched_line[3];

        // mark the cache location as clean and valid
        line[6] = 0;
        line[7] = 1;
        return 1;
    }
    uint32_t load(uint32_t addr, int whois_calling) {
        if (this->cache_in_use == false) {
            this->cache_in_use = true;
            cur_caller_id = whois_calling;
        }
        if (!(this->cache_in_use == true && whois_calling == cur_caller_id)) {
            return 0;
        }
        if (this->cache_in_use == true && whois_calling == cur_caller_id &&
            this->cache_delay_timer > 0) {
            this->cache_delay_timer -= 1;
            return 0;
        }
        // here cache_delay should be 0

        // first extracts tag, index and offset bits into variables
        // index essentially becomes which row of the cache we need to access
        // tag is verifying that it is the correct row
        // offset is which word to pick from the line.
        uint32_t tag = (uint32_t)((unsigned char)addr >> 6) & 0b1111;
        uint32_t index = (uint32_t)((unsigned char)addr >> 2) & 0b1111;
        uint32_t offset = (uint32_t)((unsigned char)addr && 0b0011);

        // loop over all 16 entries checking for the right index
        // if no valid match by end of loop, cache miss and fetch from mem
        for (int i = 0; i < 16; i++) {
            if (cache[i][0] == tag && cache[i][1] == index & cache[i][7]) {
                this->cache_delay_timer = CACHE_DELAY_DEFAULT;
                this->cache_in_use = false;
                cur_caller_id = -1;  // reset caller id
                return cache[i][2 + offset];
            }
        }
        // if we did not find the corresponding address then we have a cache
        // miss
        // std::cout << "cache miss on address" << addr << std::endl;
        if (handle_cache_miss(addr, tag, index, offset, whois_calling) == 0) {
            return 0;
        }
        // should be in the cache by now
        return load(addr, whois_calling);
    }

    uint32_t store(uint32_t addr, uint32_t data, int whois_calling) {
        // mask tag, index, offset out from addr
        if (this->cache_in_use == false) {
            this->cache_in_use = true;
            cur_caller_id = whois_calling;
        }
        if (!(this->cache_in_use == true && whois_calling == cur_caller_id)) {
            return 0;
        }
        if (this->cache_in_use == true && whois_calling == cur_caller_id &&
            this->cache_delay_timer > 0) {
            this->cache_delay_timer -= 1;
            return 0;
        }

        uint32_t tag = (uint32_t)((unsigned char)addr >> 6) & 0b1111;
        uint32_t index = (uint32_t)((unsigned char)addr >> 2) & 0b1111;
        uint32_t offset = (uint32_t)((unsigned char)addr & 0b0000000011);

        // Check if cache hit
        uint32_t* matching_line = nullptr;
        for (int i = 0; i < 16; i++) {
            if (cache[i][0] == tag && cache[i][1] == index && cache[i][7]) {
                // goes to the first word,
                matching_line = &(cache[i][2 + offset]);
            }
            // if hit, fill in the corresponding line
            if (matching_line) {
                matching_line[0] = data;
                std::cout << matching_line[0] << std::endl;

            }
            // write directly to memory
            else {
                if (this->main_mem->store(addr, data, whois_calling) ==
                    nullptr) {
                    return 0;
                } else {
                    this->cache_delay_timer = CACHE_DELAY_DEFAULT;
                    this->cache_in_use = false;
                    cur_caller_id = -1;  // reset caller id
                    return 1;            // indicating success
                }
            }
        }
        // once you reach here in the code, delay_timer should be 0, so we reset
        // memory and free it for other calls
        this->cache_delay_timer = CACHE_DELAY_DEFAULT;
        this->cache_in_use = false;
        cur_caller_id = -1;  // reset caller id
        return 1;            // indicating success
    }

    // prints out the current cache status
    void cur_status() {
        printf(
            "\n------TAG------ | -----INDEX----- | ---WORD1(00)--- | "
            "---WORD2(01)--- | ---WORD3(10)--- | ---WORD4(11)--- | "
            "-----DIRTY----- | "
            "-----VALID----- | \n");
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%15d | ", this->cache[i][j]);
            }
            printf(
                "\n--------------- | --------------- | --------------- | "
                "--------------- | --------------- | --------------- | "
                "--------------- | "
                "--------------- | \n");
        }
    }
    // assign all cache locations to NULL (essentially 0s)
    void reset() {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 8; j++) {
                // uint32_t(NULL) = 0 as it writes is as 32bits of 0
                this->cache[i][j] = uint32_t(NULL);
            }
        }
    }
};