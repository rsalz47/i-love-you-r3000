// make another file called "std_includes.h" for std libs like stdio, unistd and
// iostream etc

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>

#include "cache.cpp"
#include "memory.cpp"
using std::cout;
using std::endl;
// or put std:: before each std thing

// if fetch is false, then it is a store instruction
struct Instruction {
    bool fetch;
    uint32_t addr;
    uint32_t data;
    int caller_id;  // possibly the PC value?
    uint32_t* result = nullptr;
};

int main() {
    Memory main_mem;
    volatile int clock = 0;

    Cache main_cache;
    main_cache.reset();
    main_cache.cur_status();

    Instruction a;
    a.fetch = false;
    a.addr = 6;
    a.caller_id = 1;
    a.data = 42;

    Instruction b;
    b.fetch = true;
    b.addr = 6;
    b.caller_id = 2;
    b.data = uint32_t(NULL);

    Instruction c;
    c.fetch = false;
    c.addr = 5;
    c.caller_id = 3;
    c.data = 22;

    Instruction instruction_set[3];  // can read instructions from file into this array
    instruction_set[0] = a;
    instruction_set[1] = b;
    instruction_set[2] = c;

    uint32_t* ret_val;
    for (Instruction inst : instruction_set) {
        while (true) {
            if (inst.fetch == false) {
                inst.result =
                    main_mem.store(inst.addr, inst.data, inst.caller_id);
            }
            if (inst.fetch == true) {
                inst.result = main_mem.fetch(inst.addr, inst.caller_id);
            }

            if (inst.result != nullptr) {
                cout << inst.caller_id << " finished at " << clock << endl;
                break;
            }
            clock++;
        }
    }

    // below is code that highlights parallel memory access requests

    // uint32_t* data_addr = nullptr;
    // uint32_t* data_addr1 = nullptr;
    // uint32_t* temp = nullptr;
    // for (; clock < 200; clock++) {
    //     main_mem.store(1, 777777, 1);
    //     if (temp != nullptr) {
    //         data_addr = temp;
    //         break;
    //     }
    //     temp = main_mem.fetch(1, 2);
    //     if (temp != nullptr) {
    //         data_addr1 = temp;
    //         break;
    //     }
    // }
    // cout << clock << endl;
    // cout << *data_addr1 << endl;
}
