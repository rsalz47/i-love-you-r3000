#include "cache.h"

#include <iostream>

Cache::Cache(Memory* main_mem) {
    initial_delay = CACHE_DELAY_DEFAULT;
    cache_delay_timer = CACHE_DELAY_DEFAULT;
    cache_in_use = false;
    cur_caller_id = -1;
    this->main_mem = main_mem;

    // set the valid bits to 0
    for (int i = 0; i < 16; i++) {
        cache[i][7] = 0;
    }
}

Cache::Cache(Memory* main_mem, int delay) : Cache(main_mem) {
    initial_delay = delay;
    cache_delay_timer = delay;
}

void Cache::set_initial_delay(int delay) {
    initial_delay = delay;
    cache_delay_timer = delay;
}

void Cache::reset_delay() {
    cache_delay_timer = initial_delay;
    main_mem->reset_delay();
}

uint32_t Cache::handle_cache_miss(uint32_t addr, uint32_t tag, uint32_t index,
                                  uint32_t offset, int whois_calling) {
    // on cache miss, we need to:
    // fetch the line we want from memory
    uint32_t* fetched_line =
        this->main_mem->fetch_cache_ver(addr, whois_calling);

    if (fetched_line == nullptr) {
        return 0;
    }

    //  need a copy of the fetched_line rather, fetched_line cannot be a pointer
    //  b/c if the dirty bit is set, then data will be written back to memory
    //  thus "fetched_line" will be polluted and the cache will not update
    uint32_t fetched_line_copy[4];
    std::copy(fetched_line, fetched_line + 4, std::begin(fetched_line_copy));

    // find row in cache to evict
    // this should be trivial because it's just replace at current index
    // //bug here
    uint32_t* line = nullptr;
    // for (int i = 0; i < 16; i++) {
    //     if (cache[i][1] == tag) {
    //         line = cache[i];
    //     }
    // }
    line = cache[index];

    // if valid and dirty, evict line by writing to main mem
    if (line[7] && line[6]) {
        uint32_t addr_to_write_to = line[0];
        addr_to_write_to = addr_to_write_to << 4;
        addr_to_write_to += line[1];
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
    line[2] = fetched_line_copy[0];
    line[3] = fetched_line_copy[1];
    line[4] = fetched_line_copy[2];
    line[5] = fetched_line_copy[3];

    // mark the cache location as clean and valid
    line[6] = 0;
    line[7] = 1;
    this->num_cache_misses += 1;

    return 1;
}

uint32_t* Cache::load(uint32_t addr, int whois_calling) {
    if (this->cache_in_use == false) {
        this->cache_in_use = true;
        cur_caller_id = whois_calling;
    }
    if (!(this->cache_in_use == true && whois_calling == cur_caller_id)) {
        return nullptr;
    }
    if (this->cache_in_use == true && whois_calling == cur_caller_id &&
        this->cache_delay_timer > 0) {
        this->cache_delay_timer -= 1;
        return nullptr;
    }
    // here cache_delay should be 0

    // first extracts tag, index and offset bits into variables
    // index essentially becomes which row of the cache we need to access
    // tag is verifying that it is the correct row
    // offset is which word to pick from the line.
    uint32_t tag = (uint32_t)((unsigned char)addr >> 6) & 0b1111;
    uint32_t index = (uint32_t)((unsigned char)addr >> 2) & 0b1111;
    uint32_t offset = (uint32_t)((unsigned char)addr & 0b0000000011);

    // loop over all 16 entries checking for the right index
    // if no valid match by end of loop, cache miss and fetch from mem
    for (int i = 0; i < 16; i++) {
        if (cache[i][0] == tag && cache[i][1] == index & cache[i][7]) {
            this->cache_delay_timer = initial_delay;
            this->cache_in_use = false;
            cur_caller_id = -1;  // reset caller id
            return &(cache[i][2 + offset]);
        }
    }
    // if we did not find the corresponding address then we have a cache
    // miss
    // std::cout << "cache miss on address" << addr << std::endl;
    if (handle_cache_miss(addr, tag, index, offset, whois_calling) == 0) {
        return nullptr;
    }
    // should be in the cache by now
    return load(addr, whois_calling);
}

uint32_t* Cache::store(uint32_t addr, uint32_t data, int whois_calling) {
    // mask tag, index, offset out from addr
    if (this->cache_in_use == false) {
        this->cache_in_use = true;
        cur_caller_id = whois_calling;
    }
    if (!(this->cache_in_use == true && whois_calling == cur_caller_id)) {
        return nullptr;
    }
    if (this->cache_in_use == true && whois_calling == cur_caller_id &&
        this->cache_delay_timer > 0) {
        this->cache_delay_timer -= 1;
        return nullptr;
    }

    uint32_t tag = (uint32_t)((unsigned char)addr >> 6) & 0b0000001111;
    uint32_t index = (uint32_t)((unsigned char)addr >> 2) & 0b0000001111;
    uint32_t offset = (uint32_t)((unsigned char)addr & 0b0000000011);

    // Check if cache hit
    uint32_t* matching_line = nullptr;
    uint32_t* ret_val;  // can return cache line or memory line
    if (cache[index][7] && cache[index][0] == tag) {  // cache hit
        matching_line = &(cache[index][2 + offset]);
        matching_line[0] = data;
        cache[index][6] = 1;
        ret_val = matching_line;
    } else {
        // following write around for cache write misses
        // missed the write back to cache as it is a write miss so write
        // straight to memory instead
        ret_val = this->main_mem->store(addr, data, whois_calling);
    }

    if (ret_val == nullptr) {
        return nullptr;
    } else {
        this->cache_delay_timer = initial_delay;
        this->cache_in_use = false;
        cur_caller_id = -1;  // reset caller id
        return ret_val;      // indicating success
    }
}

void Cache::flush() {
    std::cout << "Cache flushing... Writeback to main memory" << std::endl;
    for (int i = 0; i < 16; i++) {
        // if valid and dirty, write the line back to memory
        if (cache[i][7] && cache[i][6]) {
            uint32_t base_address = (cache[i][0] << 6);  // tag component
            base_address |= (cache[i][1] << 2);          // index component
            int line_num =
                (base_address / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES);
            for (int j = 0; j < WORDS_PER_LINE; j++) {
                main_mem->memory[line_num][j] = cache[i][j + 2];
            }
            cache[i][6] = 0;
        }
    }
}

void Cache::cur_status() {
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

void Cache::reset() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            // uint32_t(NULL) = 0 as it writes is as 32bits of 0
            this->cache[i][j] = uint32_t(NULL);
        }
    }
}
