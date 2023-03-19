class Cache {
   
   public:
    // in_use
    // delay_int
    // Memroy * to main_mem
    // 4 tag + 4 index + 2 offset bits + dirty + valid
    uint32_t cache[16][8];

    int load(uint32_t addr) {
        // first extracts tag, index and offset bits into variables
        // index essentially becomes which row of the cache we need to access
        // tag is verifying that it is the correct row
        // offset is which word to pick from the line.

        // extract index
        // go to that index and check valid bit, if not valid load line from //
        // cache miss here memory if valid ok, compare tag bit. if tags do not
        // match load line from memory, set valid = 1 if tags match, return
        // value from word // cache hit
        return -1;
    }

    int store(uint32_t addr, uint32_t data) { return -1;}

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

