
// RAM address is currently 26 bits
// we need atleast 4 words in a line for our cache
struct cache_access {
    int sucess;
    uint32_t data;
    uint32_t addr;
    int delay_timer;
};

class Cache {
   public:
    // current plan is to do 3 tag + 4 index + 3 offset bits + dirty + valid
    uint32_t cache[16][8];

    int load(cache_access cache_req) {
        // first extracts tag, index and offset bits into variables
        //  index essentially becomes which row of the cache we need to access
        //  tag is verifying that it is the correct row
        // offset is which word to pick from the line.

        // extract index
        // go to that index and check valid bit, if not valid load line from
        // memory if valid ok, compare tag bit. if tags do not match load line
        // from memory, set valid = 1 if tags match, return value from word
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

// TODO: later
// class Cache {
//    public:
//        Memory* next_level_down; // Issue: what if next level down is another
//        cache? Ask prof, think cache and mem are different enough that they
//        can't be same int* cache; //should be 2D
//
//        Cache(cache_size) {
//          cache = malloc(cache_size);
//        }
//
//        int load_from_cache(addr, int* delay int) {
//            //check if it is currently in the cache, i.e. the array class
//            member
//            //else, load from next level down
//            return -1;
//        }
//
//
//}