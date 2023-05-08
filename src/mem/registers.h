#include <map>
#include <string>

// This simulator supports 32 bit registers. Therefore, each register maps to an address 
// that is 8 bytes away from each other.
std::map<std::string, unsigned long> RegistersToBits {
    {"r0", (unsigned long)      0b0},
    {"r1", (unsigned long)      0b1},
    {"r2", (unsigned long)     0b10},
    {"r3", (unsigned long)     0b11},
    {"r4", (unsigned long)    0b100},
    {"r5", (unsigned long)    0b101},
    {"r6", (unsigned long)    0b110},
    {"r7", (unsigned long)    0b111},
    {"r8", (unsigned long)   0b1000},
    {"r9", (unsigned long)   0b1001},
    {"r10", (unsigned long)  0b1010},
    {"r11", (unsigned long)  0b1011},
    {"r12", (unsigned long)  0b1100},
    {"r13", (unsigned long)  0b1101},
    {"r14", (unsigned long)  0b1110},
    {"r15", (unsigned long)  0b1111},
    {"r16", (unsigned long) 0b10000},
};



// write to register()
// read from register()
