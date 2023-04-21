#ifndef CACHE_H
#define CACHE_H

#include <algorithm>
#include <iterator>
#include "memory_system.h"
#include "memory.h"

#define CACHE_DELAY_DEFAULT 2

class Cache : public MemorySystem {
   public:
	int initial_delay;
    int cache_delay_timer;
    bool cache_in_use;
    int cur_caller_id = -1;
    Memory* main_mem;

    int num_cache_misses = 0;
    // Memory * to main_mem
    // 4 tag + 4 index + 2 offset bits + dirty + valid
    uint32_t cache[16][8];

    Cache(Memory* main_mem);

	Cache(Memory* main_mem, int delay);

	void set_initial_delay(int delay);

    uint32_t handle_cache_miss(uint32_t addr, uint32_t tag, uint32_t index,
                               uint32_t offset, int whois_calling);
    
    uint32_t* load(uint32_t addr, int whois_calling);

    uint32_t* store(uint32_t addr, uint32_t data, int whois_calling);

    // prints out the current cache status
    void cur_status();
    
    // assign all cache locations to NULL (essentially 0s)
    void reset();
    void reset_delay();
};
#endif /* CACHE_H */
