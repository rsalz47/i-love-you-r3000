#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "memory_system.h"

#define WORDS_PER_LINE 4
#define NUM_LINES 256
#define DEFAULT_DELAY 5

class Memory : public MemorySystem {
   public:
	int initial_delay = DEFAULT_DELAY;
    int delay_timer = DEFAULT_DELAY;
    // will be polled by function calling load or store
    bool in_use = false;
    // pipeline*
    int cur_caller_id = -1;  // this is to return to the correct person to be
                             // replaced with pipeline stage

    // spent an hour debugging this. using memory[524288][4] is too large for
    // the code stack. using defaults from slides
    uint32_t memory[NUM_LINES][WORDS_PER_LINE];

	// default constructor
	Memory();
	
	Memory(int delay);

	void set_initial_delay(int delay);
	
    // This returns a pointer to the start of the matching line of the addr. For
    // example, for addr 9, with line length 4, it will return memory[2][0] as
    // the address.

    // to access the rest of the words, you simply add the word offset to the
    // returned address for example,
    //    cout << *(main_mem.fetch_cache_ver(addr 9)<this will return
    //    memory[2][0] / addr 8> + 1<adding 1 to addr 8 will give addr 9 >) <<
    //    endl;
    uint32_t* fetch_cache_ver(uint32_t addr,int whois_calling);
    
    uint32_t* store_cache_ver(uint32_t addr, uint32_t data);
    
    uint32_t* load(uint32_t addr, int whois_calling);
    
    uint32_t* store(uint32_t addr, uint32_t data, int whois_calling);

    void flush();

    // assign all memory locations to NULL (essentially 0s)
    void reset();
    void reset_delay();

    // prints out a formatted memory status in the terminal
    void cur_status();
};


#endif /* MEMORY_H */
