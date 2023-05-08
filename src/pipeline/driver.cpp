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

    memory.memory[0][0] = 0b10000100000000000000000000000100;
    memory.memory[0][1] = 0b10000100001000000000000000000000;
    memory.memory[0][2] = 0b10000100010000000000000000000000;
    memory.memory[0][3] = 0b10000100011000000000000000000000;
    memory.memory[1][0] = 0b10000100100000000000000000000000;
    memory.memory[1][1] = 0b10000100101000000000000000100000;
    memory.memory[1][2] = 0b10000100110000000000000000110000;
    memory.memory[1][3] = 0b10000110000000000000000001000000;
    memory.memory[2][0] = 0b10000100001000000000000000000000;
    memory.memory[2][1] = 0b00001000111000100000000000000000;
    memory.memory[2][2] = 0b00000000111001000011100000000000;
    memory.memory[2][3] = 0b00000000111001010011100000000000;
    memory.memory[3][0] = 0b10000001000001110000000000000000;
    memory.memory[3][1] = 0b00001001001001000000000000000000;
    memory.memory[3][2] = 0b00000001001000110100100000000000;
    memory.memory[3][3] = 0b00000001001001100100100000000000;
    memory.memory[4][0] = 0b10000001010010010000000000000000;
    memory.memory[4][1] = 0b00001001010010000101000000000000;
    memory.memory[4][2] = 0b00000000001000010101000000000000;
    memory.memory[4][3] = 0b01011100100001000000000000000001;
    memory.memory[5][0] = 0b10010000000001000000000000001001;
    memory.memory[5][1] = 0b00001001111000100000000000000000;
    memory.memory[5][2] = 0b00000001111000110111100000000000;
    memory.memory[5][3] = 0b00000001111100000111100000000000;
    memory.memory[6][0] = 0b01111100001011110000000000000000;
    memory.memory[6][1] = 0b01011100011000110000000000000001;
    memory.memory[6][2] = 0b10010000000000110000000000001000;
    memory.memory[6][3] = 0b01011100010000100000000000000001;
    memory.memory[7][0] = 0b10000100011000000000000000000000;
    memory.memory[7][1] = 0b10010000000000100000000000001000;
    memory.memory[7][2] = 0b11111100000000000000000000000000;

    // array 1
    memory.memory[8][0] = 1;
    memory.memory[8][1] = 2;
    memory.memory[8][2] = 3;
    memory.memory[8][3] = 4;
    memory.memory[9][0] = 5;
    memory.memory[9][1] = 6;
    memory.memory[9][2] = 7;
    memory.memory[9][3] = 8;
    memory.memory[10][0] = 1;
    memory.memory[10][1] = 2;
    memory.memory[10][2] = 3;
    memory.memory[10][3] = 4;
    memory.memory[11][0] = 5;
    memory.memory[11][1] = 6;
    memory.memory[11][2] = 7;
    memory.memory[11][3] = 8;

    // array 2
    memory.memory[12][0] = 5;
    memory.memory[12][1] = 6;
    memory.memory[12][2] = 7;
    memory.memory[12][3] = 8;
    memory.memory[13][0] = 1;
    memory.memory[13][1] = 2;
    memory.memory[13][2] = 3;
    memory.memory[13][3] = 4;
    memory.memory[14][0] = 5;
    memory.memory[14][1] = 6;
    memory.memory[14][2] = 7;
    memory.memory[14][3] = 8;
    memory.memory[15][0] = 1;
    memory.memory[15][1] = 2;
    memory.memory[15][2] = 3;
    memory.memory[15][3] = 4;
    
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
