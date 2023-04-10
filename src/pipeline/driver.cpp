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
uint32_t registers[32];

int main() {
    // initializations (right now, just confirming stuff gets instantiated)
    memory.set_initial_delay(0);
    std::cout << memory.initial_delay << std::endl;

    cache.set_initial_delay(0);
    std::cout << cache.initial_delay << std::endl;


    // sw r0 r1 0
    memory.memory[0][0] = 0b01111100000000010000000000000000;
    registers[0] = 10;
    registers[1] = 20;

    // lw r3 r4 0, load the data stored in addr r4 and write it to r3
    memory.memory[0][1] = 0b10000000011001000000000000000000;
    registers[4] = 100;
    memory.memory[25][0] = 24;

    //beq r5 r6 0
    memory.memory[0][2] = 0b10001100101001100000000000000000;

    //add r1 r2 r3
    memory.memory[0][3] = 0b00000000001000100001100000000000;
        
    WritebackStage wb_stage(registers, &PROGRAM_COUNTER);
    MemoryStage mem_stage(wb_stage, &cache);
    ExecuteStage execute_stage(mem_stage);
    DecodeStage decode_stage(execute_stage, registers);
    FetchStage fetch_stage(&PROGRAM_COUNTER, &cache, decode_stage);

    while(CLK < 16) {
        std::cout << "current clock: " << CLK << std::endl;
        wb_stage.tick();
        if (wb_stage.squashed) {
            std::cout << "!! squashing previous stages" << std::endl;
            wb_stage.noop = true;
            mem_stage.noop = true;
            execute_stage.noop = true;
            decode_stage.noop = true;
        }
        mem_stage.tick();
        execute_stage.tick();
        decode_stage.tick();
        fetch_stage.tick();
        CLK++;
        std::cout << std::endl;

    }

    std::cout << "addr: " << memory.memory[5][0] << std::endl; // should be 10
    std::cout << "r3: " << registers[3] << std::endl; // should be 24
    return 0;
}
