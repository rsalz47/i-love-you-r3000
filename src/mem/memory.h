#include <iostream>
#include <map>
#include <string>

// 2^26 total mem bits / 2^5 int32_t bits gives us 2^21 = 2097152 bits -> indexes of memory / 4 (to exploit spacial locality) = 2^19 = 524288
// Signed int32_t type -> signed arithmetic <---- RS: no need, we can cast to signed if need be, starting w/ signed can introduce errors

uint32_t registers[32];

uint32_t memory[524288][4]; // this means each cache line is 128 bits

/*
* RS: I don't think these register macros will come in handy, unfortunately
* only know what register we're working with after we parse it out of the instruction
* we won't be specifying any registers ourselves
* (also have concerns about reg0/reg1/... being used in code looking too much like asm)
*/

// method to access registers. accessing the value in registers is as easy as saying val = reg0.
#define reg0  registers[0b00000]
#define reg1  registers[1]
#define reg2  registers[2]
#define reg3  registers[3] 
#define reg4  registers[4]
#define reg5  registers[5]
#define reg6  registers[6]
#define reg7  registers[0b00111] 
#define reg8  registers[8]
#define reg9  registers[9]
#define reg10 registers[10]
#define reg11 registers[11] 
#define reg12 registers[12]
#define reg13 registers[13]
#define reg14 registers[14]
#define reg15 registers[15] 
#define reg16 registers[16]
#define reg17 registers[17]
#define reg18 registers[18]
#define reg19 registers[19] 
#define reg20 registers[20]
#define reg21 registers[21]
#define reg22 registers[22]
#define reg23 registers[23] 
#define reg24 registers[24]
#define reg25 registers[25]
#define reg26 registers[26]
#define reg27 registers[27] 
#define reg28 registers[28]
#define reg29 registers[29]
#define reg30 registers[30]
#define reg31 registers[31]

int32_t read_from_memory(uint32_t address)
{
    int32_t ret_val = memory[(address / 4) % 256][address % 4];
    return ret_val;
}

void write_to_memory(uint32_t address, int32_t value)
{
    memory[(address / 4) % 256][address % 4] = value;
    return;
}
