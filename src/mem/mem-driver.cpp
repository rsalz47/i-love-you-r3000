// make another file called "std_includes.h" for std libs like stdio, unistd and iostream etc

#include <stdio.h>
#include <unistd.h> 
#include <iostream>
#include <stdint.h>
#include "memory.h"
#define MEM_DELAY 100
using namespace std;

int main()
{
    int delay1 = MEM_DELAY;
    int delay2 = MEM_DELAY;
    Memory main_mem;
    main_mem.store(1, uint32_t(7777), &delay1);
    main_mem.store(2, uint32_t(7777), &delay1);
    main_mem.store(3, uint32_t(7777), &delay1);
    main_mem.store(4, uint32_t(7777), &delay1);
    main_mem.store(123,uint32_t(7777),&delay1);
    main_mem.cur_status();
    cout << main_mem.fetch(4,&delay2) << endl;
    // cout << main_mem.fetch(2,&delay2) << endl;
    // main_mem.reset();
    return 0;
}