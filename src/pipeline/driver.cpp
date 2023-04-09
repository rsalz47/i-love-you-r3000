#include "fetch.cpp"
#include "decode.cpp"
#include "execute.cpp"
//#include "memacc.cpp"
//#include "writeback.cpp"
#include <iostream>
#include "../mem/cache.cpp"

uint32_t CLK = 0;
uint32_t PROGRAM_COUNTER = 0;
Memory memory(10);
Cache cache(&memory, 5);

int main() {
    // initializations (right now, just confirming stuff gets instantiated)
    memory.set_initial_delay(999);
    std::cout << memory.initial_delay << std::endl;

    cache.set_initial_delay(888);
    std::cout << cache.initial_delay << std::endl;
    
    FetchStage fetch_stage(&PROGRAM_COUNTER, &cache);
    DecodeStage decode_stage(fetch_stage);

    
    // while(true) {
        // writeback.tick();
        // memory.tick();
        // execute.tick();
        // decode.tick();
        // fetch.tick();
    // }

    return 0;
}
