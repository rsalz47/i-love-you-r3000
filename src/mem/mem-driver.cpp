#include <iostream>
#include "memory.h"

using namespace std;


int main() {
    reg7 = 1231;
    uint32_t address = 0;
    write_to_memory(0,reg7);
    cout << read_from_memory(0);
    // print out clock cycles taken
    // run with time (unix function)
    return 0;
}
