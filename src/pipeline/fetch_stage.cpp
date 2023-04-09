#include "fetch_stage.h"

FetchStage::FetchStage(uint32_t* program_counter, Cache* ch, DecodeStage &d)
    : pc(program_counter), cache(ch), decode_stage(d) {}

// The tick method is what happens every clock cycle.
// In the fetch stage of a pipeline, this is one of two things:
//      1) Begin a memory access for the next instruction (which will be the program counter)
//      2) Wait for memory to return the results of the current access
void FetchStage::tick() {
    // If we are not blocked because of a memory access, begin a memory access
    if(!blocked) {
        std::cout << "Fetch: Now beginning a new fetch at address " << *pc << ", blocking." << std::endl;
        blocked = true;
        curr_addr_fetching = *pc;
        result = cache->load(curr_addr_fetching, 0);        
    }
    // if we are blocked and we do not have a result back yet, then we are waiting for memory to finish
    else if(blocked && result == nullptr){
        std::cout << "Fetch: Currently stalled, polling for address " << *pc << std::endl;
        result = cache->load(curr_addr_fetching, 0); 
    }

    // if we have the data we need, see if we can pass it forward
    if(result != nullptr) {
        std::cout << "Fetch: Memory access to " << " finished, no longer blocked." << std::endl;
        std::cout << "Fetch: Delivering instruction " << result << " to Decode" << std::endl;
        if(decode_stage.blocked) {
            std::cout << "Fetch: Instruction not delivered because Decode is blocked. Trying again next cycle." << std::endl;
            return;
        }
        else {
            decode_stage.encoded_instruction = *result; 
            std::cout << "Fetch: Instruction " << decode_stage.encoded_instruction << " delivered to Decode." << std::endl;
            result = nullptr;
            // increment pc
            *pc = *pc + 1;
            blocked = false;                        
        }
    }
}
