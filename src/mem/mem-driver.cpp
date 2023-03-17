// make another file called "std_includes.h" for std libs like stdio, unistd and
// iostream etc

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "memory.h"
#define MEM_DELAY 100
using namespace std;

int main() {
    Memory main_mem;
    volatile int clock;

    mem_access store_req1 = {
        0,              // sucess
        uint32_t(777),  // data
        6,              // addr
        10              // delay int
    };

    mem_access fetch_req1 = {
        0,               // sucess
        uint32_t(NULL),  // data
        6,               // addr
        5                // delay int
    };

    //TODO switch to while(clock++) when we need to let the clock run to infinity/ EOF

    for (clock = 0; clock < 200; clock++) {
        // main_mem.store is called in every iteration of the for loop until it
        // returns 1
        if (main_mem.store(&store_req1) > 0) {
            cout << store_req1.sucess << endl;
            break;  // stops ticking of clock as the access is finished here
        }
    }
    for (;clock < 200; clock++) {
        // main_mem.fetch is called in every iteration of the for loop until it
        // returns 1
        if (main_mem.fetch(&fetch_req1) > 0) {
            cout << fetch_req1.data << endl;
            break;  // stops ticking of clock as the access is finished here
        }
    }
}