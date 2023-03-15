class Memory {
    public:
        int default_delay;

        int load(uint_32 addr, int* delay_int) {
            // after waiting the appropriate amount of time,
            // load from the memory array at ADDR
            return -1;
        }

        int store(uint_32 addr, int* delay_int) {
            // after waiting the appropriate amount of time,
            // store DATA in the memory array at ADDR
            return -1;
        }
};


// TODO: later
class Cache {
    public:
        Memory* next_level_down; // Issue: what if next level down is another cache? Ask prof, think cache and mem are different enough that they can't be same
        int* cache; //should be 2D

        Cache(cache_size) {
          cache = malloc(cache_size);  
        }
    
        int load_from_cache(addr, int* delay int) {
            //check if it is currently in the cache, i.e. the array class member
            //else, load from next level down
            return -1;
        }


}

