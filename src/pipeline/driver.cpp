#include "fetch_stage.h"
#include "decode_stage.h"
#include "execute_stage.h"
#include "memory_stage.h"
#include "writeback_stage.h"

//#include "memacc.cpp"
//#include "writeback.cpp"
#include <iostream>
#include "../mem/cache.h"

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

    WritebackStage wb_stage;
    MemoryStage mem_stage(wb_stage, &cache);
    ExecuteStage execute_stage(mem_stage);
    DecodeStage decode_stage(execute_stage);
    FetchStage fetch_stage(&PROGRAM_COUNTER, &cache, decode_stage);

    
    while(true) {
        wb_stage.tick();
        mem_stage.tick();
        execute_stage.tick();
        decode_stage.tick();
        fetch_stage.tick();
    }

    return 0;
}
