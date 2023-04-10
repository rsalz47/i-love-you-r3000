#ifndef FETCH_STAGE_H
#define FETCH_STAGE_H

#include <fstream>
#include <iostream>
#include "../mem/cache.h"
#include "decode_stage.h"

class FetchStage {
 private:
    uint32_t* pc;
    uint32_t curr_addr_fetching; // This variable is needed in the case that the pc changes while we are in the middle of a fetch 
    Cache* cache;
    DecodeStage &decode_stage;

 public:
    bool blocked = false;
    uint32_t* result = nullptr;
    
    // The member variables are pointers because they are shared amongst all pipeline stages
    // This constructor simply initializes them
    FetchStage(uint32_t* program_counter, Cache* ch, DecodeStage &d);

    void reset();
    // The tick method is what happens every clock cycle.
    // In the fetch stage of a pipeline, this is one of two things:
    //      1) Begin a memory access for the next instruction (which will be the program counter)
    //      2) Wait for memory to return the results of the current access
    void tick();
};
#endif /* FETCH_STAGE_H */
