#include "fetch_stage.h"
#include "decode_stage.h"
#include "execute_stage.h"
#include "memory_stage.h"
#include "writeback_stage.h"

#include <iostream>
#include <vector>
#include "../mem/cache.h"

uint32_t CLK = 0;
uint32_t PROGRAM_COUNTER = 0;
Memory memory(10);
Cache cache(&memory, 5);
uint32_t registers[32];

std::vector<int> dependency_list;

MemorySystem *mem_sys = &cache; // cache enabled

void enable_cache(FetchStage& fetch_stage, MemoryStage& memory_stage, Cache* cache) {
    fetch_stage.set_mem_sys(cache);
    memory_stage.set_mem_sys(cache);
}

void disable_cache(FetchStage& fetch_stage, MemoryStage& memory_stage, Memory* memory) {
    fetch_stage.set_mem_sys(memory);
    memory_stage.set_mem_sys(memory);
}


int main() {
    std::string temp;
    // initializations (right now, just confirming stuff gets instantiated)
    memory.set_initial_delay(0);
    std::cout << memory.initial_delay << std::endl;


    cache.set_initial_delay(0);
    std::cout << cache.initial_delay << std::endl;

    /**
    memory.memory[0][0] = 0b10000100000000000000000000000000;
    memory.memory[0][1] = 0b10000100001000000000000000000001;
    memory.memory[0][2] = 0b10000100010000000000000000000101;
    memory.memory[0][3] = 0b00000000000000010000000000000000;
    memory.memory[1][0] = 0b10010000000000100000000000000011;
    memory.memory[1][1] = 0b10000100100000000000000001100100;
    memory.memory[1][2] = 0b11111100000000000000000000000000;
    **/

    /**
    memory.memory[0][0] = 0b10000100001000000000000000000010;
    memory.memory[0][1] = 0b10000100010000000000000000000011;
    memory.memory[0][2] = 0b00000000000000010001000000000000;
    memory.memory[0][3] = 0b11111100000000000000000000000000;
    **/

    memory.memory[0][0] = 0b10000100000000000000000000000000;
    memory.memory[0][1] = 0b10000100001000000000000000000100;
    memory.memory[0][2] = 0b10000100010000000000000000000000;
    memory.memory[0][3] = 0b10000000100000000000000000010100;
    memory.memory[1][0] = 0b10000000101000000000000000011000;
    memory.memory[1][1] = 0b00001000110001010010000000000000;
    memory.memory[1][2] = 0b00000000010000100011000000000000;
    memory.memory[1][3] = 0b01011100000000000000000000000001;
    memory.memory[2][0] = 0b10010000000000010000000000000011;
    memory.memory[2][1] = 0b01111100010000010000000000101000;
    memory.memory[2][2] = 0b11111100000000000000000000000000;

    // vector 1
    memory.memory[5][0] = 0b1;
    memory.memory[5][1] = 0b10;
    memory.memory[5][2] = 0b11;
    memory.memory[5][3] = 0b100;

    // vector 2
    memory.memory[6][0] = 0b101;
    memory.memory[6][1] = 0b110;
    memory.memory[6][2] = 0b111;
    memory.memory[6][3] = 0b1000;

    

    WritebackStage wb_stage(registers, &PROGRAM_COUNTER, dependency_list);
    MemoryStage mem_stage(wb_stage, mem_sys);
    ExecuteStage execute_stage(mem_stage);
    DecodeStage decode_stage(execute_stage, registers, dependency_list);
    FetchStage fetch_stage(&PROGRAM_COUNTER, mem_sys, decode_stage);
    //fetch_stage.disable_pipeline(); // disable pipeline
    // one can also disable the pipeline using the fetch constructor
    // fetch_stage(&PROGRAM_COUNTER, &cache, decode_stage, true);

    // disable_cache(fetch_stage, mem_stage, &memory); // disable cache

    while(true) {
        std::cout << "CLOCK: " << CLK << std::endl;
        std::cout << "PROGRAM COUNTER: " << PROGRAM_COUNTER << std::endl;
        if (wb_stage.exit) {
            break; // in gui code, just return
        }
        wb_stage.tick();
        if (wb_stage.exit || wb_stage.squashed) {
            std::cout << "!! CLEARING DEPENDENCY LIST  !!" << std::endl;
            dependency_list.clear();
            std::cout << "!! SQUASHING PREVIOUS STAGES !!" << std::endl;
            mem_stage.reset();
            execute_stage.reset();
            decode_stage.reset();
            fetch_stage.reset();
        } 
        else {
            mem_stage.tick();
            std::cout << "Register 4 expected 100, is: " << registers[4] << std::endl;
            std::cout << "Register 0 expected 5, is: " << registers[0] << std::endl;
            execute_stage.tick();
            decode_stage.tick();
            fetch_stage.tick();
        }
        CLK++;
    }

    std::cout << "Register 2 expected 70, is: " << registers[2] << std::endl;
    std::cout << "Memory[44] is: " << memory.memory[11][0] << std::endl; 

    return 0;
}
