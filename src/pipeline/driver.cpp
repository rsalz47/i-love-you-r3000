#include "fetch_stage.h"
#include "decode_stage.h"
#include "execute_stage.h"
#include "memory_stage.h"
#include "writeback_stage.h"

#include <iostream>
#include "../mem/cache.h"

uint32_t CLK = 0;
uint32_t PROGRAM_COUNTER = 0;
Memory memory(10);
Cache cache(&memory, 5);
uint32_t registers[32];

int main() {
    std::string temp;
    // initializations (right now, just confirming stuff gets instantiated)
    memory.set_initial_delay(0);
    std::cout << memory.initial_delay << std::endl;

    cache.set_initial_delay(0);
    std::cout << cache.initial_delay << std::endl;

    memory.memory[0][0] = 0b10000100001000000000000000000011;
    memory.memory[0][1] = 0b10001000000000000000000000000011;
    memory.memory[0][2] = 0b10000100001000000000000000001010;
    memory.memory[0][3] = 0b10000100001000000000000000010100;
    memory.memory[1][0] = 0b11111100000000000000000000000000; // hcf

    WritebackStage wb_stage(registers, &PROGRAM_COUNTER);
    MemoryStage mem_stage(wb_stage, &cache);
    ExecuteStage execute_stage(mem_stage);
    DecodeStage decode_stage(execute_stage, registers);
    FetchStage fetch_stage(&PROGRAM_COUNTER, &cache, decode_stage);

    while(CLK < 100) {
        std::cout << "CLOCK: " << CLK << std::endl;
        std::cout << "PROGRAM COUNTER: " << PROGRAM_COUNTER << std::endl;
        if (wb_stage.exit) {
            break; // in gui code, just return
        }
        wb_stage.tick();
        if (wb_stage.exit || wb_stage.squashed) {
            std::cout << "!! squashing previous stages" << std::endl;
            mem_stage.reset();
            execute_stage.reset();
            decode_stage.reset();
            fetch_stage.reset();
        }

        mem_stage.tick();
        execute_stage.tick();
        decode_stage.tick();
        fetch_stage.tick();

        CLK++;
        // std::cin >> temp;
    }

    std::cout << "addr: " << memory.memory[5][0] << std::endl; // should be 10
    std::cout << "r1: " << registers[1] << std::endl; // should be 24
    return 0;
}
