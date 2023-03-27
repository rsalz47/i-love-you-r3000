// make another file called "std_includes.h" for std libs like stdio, unistd and
// iostream etc

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>

#include "cache.cpp"  // cache.cpp includes memory.cpp
using std::cout;
using std::endl;
// or put std:: before each std thing
struct Instruction {
    bool fetch;
    uint32_t addr;
    uint32_t data;
    int caller_id;  // possibly the PC value?
    int result = -1;
};
int main() {
    Memory main_mem;
    volatile int clock = 0;

    Cache main_cache = Cache(&main_mem);
    main_cache.reset();

    Instruction a;
    a.fetch = false;
    a.addr = 1;
    a.caller_id = 1;
    a.data = 42;

    Instruction b;
    b.fetch = true;
    b.addr = 1;
    b.caller_id = 2;
    b.data = 0;

    Instruction c;
    c.fetch = false;
    c.addr = 6;
    c.caller_id = 3;
    c.data = 77;

    Instruction d;
    d.fetch = true;
    d.addr = 6;
    d.caller_id = 4;
    d.data = 0;

    Instruction e;
    e.fetch = true;
    e.addr = 6;
    e.caller_id = 5;
    e.data = 0;

    Instruction
        instruction_set[5];  // can read instructions from file into this array
    instruction_set[0] = a;
    instruction_set[1] = b;
    instruction_set[2] = c;
    instruction_set[3] = d;
    instruction_set[4] = e;
    uint32_t* ret_val;

    for (Instruction inst : instruction_set) {
        while (true) {
            if (inst.fetch == false) {
                inst.result =
                    main_cache.store(inst.addr, inst.data, inst.caller_id);
            }
            if (inst.fetch == true) {
                inst.result = main_cache.load(inst.addr, inst.caller_id);
            }

            if (inst.result != 0) {
                cout << inst.caller_id << " finished at " << clock << endl;
                break;
            }
            clock++;
        }
    }
    main_cache.cur_status();
    cout << "\n" << endl;
    main_mem.cur_status();
}