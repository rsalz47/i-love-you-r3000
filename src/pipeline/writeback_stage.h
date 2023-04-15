#ifndef WRITEBACK_STAGE_H
#define WRITEBACK_STAGE_H

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

typedef struct executed_instruction {
    // TO BE FIXED
    // R-format: opcode + destination + value
    // I-format: opcode + destination + value
    //          store:  opcode + dest_value + value
    //          branch: opcode + branch_taken + addr
    // J-format: opcode + addr
    
    char opcode; // opcode of the instruction
    char destination;
    uint32_t dest_value; // signed?
    int32_t value;
    uint32_t addr;
    bool branch_taken; // the flag records whether branch is taken for branch instructions
} executed_instruction;


class WritebackStage {
 private:
	uint32_t* pc;
	uint32_t* registers;
	//pending registers?

 public:
    bool noop = true;
    bool squashed = false; // indicates whether the previous stages should be squashed
    bool exit = false; // the program should exit
    executed_instruction executed;
    
    WritebackStage(uint32_t* regs, uint32_t* program_counter);
	void tick();
};
#endif /* WRITEBACK_STAGE_H */
