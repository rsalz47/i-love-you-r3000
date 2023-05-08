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

void load_instructions_matmul() {
    memory.memory[0][0] = 2216689665;
    memory.memory[0][1] = 2082472032;
    memory.memory[0][2] = 2216689666;
    memory.memory[0][3] = 2082472033;
    memory.memory[1][0] = 2216689667;
    memory.memory[1][1] = 2082472034;
    memory.memory[1][2] = 2216689668;
    memory.memory[1][3] = 2082472035;
    memory.memory[2][0] = 2216689669;
    memory.memory[2][1] = 2082472036;
    memory.memory[2][2] = 2216689670;
    memory.memory[2][3] = 2082472037;
    memory.memory[3][0] = 2216689671;
    memory.memory[3][1] = 2082472038;
    memory.memory[3][2] = 2216689672;
    memory.memory[3][3] = 2082472039;
    memory.memory[4][0] = 2216689665;
    memory.memory[4][1] = 2082472040;
    memory.memory[4][2] = 2216689666;
    memory.memory[4][3] = 2082472041;
    memory.memory[5][0] = 2216689667;
    memory.memory[5][1] = 2082472042;
    memory.memory[5][2] = 2216689668;
    memory.memory[5][3] = 2082472043;
    memory.memory[6][0] = 2216689669;
    memory.memory[6][1] = 2082472044;
    memory.memory[6][2] = 2216689670;
    memory.memory[6][3] = 2082472045;
    memory.memory[7][0] = 2216689671;
    memory.memory[7][1] = 2082472046;
    memory.memory[7][2] = 2216689672;
    memory.memory[7][3] = 2082472047;
    memory.memory[8][0] = 2216689669;
    memory.memory[8][1] = 2082472048;
    memory.memory[8][2] = 2216689670;
    memory.memory[8][3] = 2082472049;
    memory.memory[9][0] = 2216689671;
    memory.memory[9][1] = 2082472050;
    memory.memory[9][2] = 2216689672;
    memory.memory[9][3] = 2082472051;
    memory.memory[10][0] = 2216689665;
    memory.memory[10][1] = 2082472052;
    memory.memory[10][2] = 2216689666;
    memory.memory[10][3] = 2082472053;
    memory.memory[11][0] = 2216689667;
    memory.memory[11][1] = 2082472054;
    memory.memory[11][2] = 2216689668;
    memory.memory[11][3] = 2082472055;
    memory.memory[12][0] = 2216689669;
    memory.memory[12][1] = 2082472056;
    memory.memory[12][2] = 2216689670;
    memory.memory[12][3] = 2082472057;
    memory.memory[13][0] = 2216689671;
    memory.memory[13][1] = 2082472058;
    memory.memory[13][2] = 2216689672;
    memory.memory[13][3] = 2082472059;
    memory.memory[14][0] = 2216689665;
    memory.memory[14][1] = 2082472060;
    memory.memory[14][2] = 2216689666;
    memory.memory[14][3] = 2082472061;
    memory.memory[15][0] = 2216689667;
    memory.memory[15][1] = 2082472062;
    memory.memory[15][2] = 2216689668;
    memory.memory[15][3] = 2082472063;
    memory.memory[16][0] = 2214592516;
    memory.memory[16][1] = 2216689664;
    memory.memory[16][2] = 2218786816;
    memory.memory[16][3] = 2220883968;
    memory.memory[17][0] = 2222981120;
    memory.memory[17][1] = 2225078368;
    memory.memory[17][2] = 2227175536;
    memory.memory[17][3] = 2248146944;
    memory.memory[18][0] = 2216689664;
    memory.memory[18][1] = 2222981120;
    memory.memory[18][2] = 149028864;
    memory.memory[18][3] = 14956544;
    memory.memory[19][0] = 15022080;
    memory.memory[19][1] = 2164719616;
    memory.memory[19][2] = 153354240;
    memory.memory[19][3] = 19089408;
    memory.memory[20][0] = 19286016;
    memory.memory[20][1] = 2169044992;
    memory.memory[20][2] = 155734016;
    memory.memory[20][3] = 2183168;
    memory.memory[21][0] = 1552154625;
    memory.memory[21][1] = 2416181322;
    memory.memory[21][2] = 165806080;
    memory.memory[21][3] = 31684608;
    memory.memory[22][0] = 32536576;
    memory.memory[22][1] = 2083454976;
    memory.memory[22][2] = 1549991937;
    memory.memory[22][3] = 2416115784;
    memory.memory[23][0] = 1547829249;
    memory.memory[23][1] = 2220883968;
    memory.memory[23][2] = 2416050248;
    memory.memory[23][3] = 4227858432;

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
    load_instructions_matmul();
    
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

    return 0;
}
