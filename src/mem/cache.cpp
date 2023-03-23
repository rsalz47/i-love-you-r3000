class Cache {
    public:
   // in_use
    // delay_int
    // Memory * to main_mem
    // 4 tag + 4 index + 2 offset bits + dirty + valid
    uint32_t cache[16][8];

    void handle_cache_miss(uint32_t addr, uint32_t tag, 
                           uint32_t index, uint32_t offset) {
        // on cache miss, we need to:
        // fetch the line we want from memory
        uint32_t fetched_line = main_mem->fetch_cache_ver(addr);
        // find row in cache to evict
            // this should be trivial because it's just replace at current index
        uint32* line = nullptr;
        for(int i = 0; i < 16; i++) {
            if(cache[i][1] == tag) {
                line = cache[i]; 
            }
        }
        
        // if dirty, evict line by writing to main mem
        if(line[6]) {
            // main_mem->write_cache_ver(addr_from_cache_line);
        }
        // load in new data with appropriate tag/index/offset
        line[0] = tag;
        line[1] = index;
        
        // mark the cache location as clean and valid
        line[6] = 0;
        line[7] = 1;
    }

    uint32_t load(uint32_t addr) {
        // first extracts tag, index and offset bits into variables
        // index essentially becomes which row of the cache we need to access
        // tag is verifying that it is the correct row
        // offset is which word to pick from the line.
        uint32_t tag = (uint32_t) ((unsigned char) addr >> 6) & 0b1111;
        uint32_t index = (uint32_t) ((unsigned char) addr >> 2) & 0b1111;
        uint32_t offset = (uint32_t) ((unsigned char) addr && 0b0011);

        // loop over all 16 entries checking for the right index
        // if no valid match by end of loop, cache miss and fetch from mem
        for(int i = 0; i < 16; i++) {
            if(cache[i][1] == tag && cache[i][7]) {
                return cache[i][2 + offset];
            }
        }
        // if we did not find the corresponding address then we have a cache miss 
        cout << "cache miss on address" << addr << endl;
        handle_cache_miss(addr);

        // should be in the cache by now 
        return load(addr);
    }

    int store(uint32_t addr, uint32_t data) {
        // mask tag, index, offset out from addr
        // Check if cache hit
        // if(cache_hit) {
        //      write data to cache
        // }
        // write_to_mem(addr, data);
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

