#ifndef WRITEBACK_STAGE_H
#define WRITEBACK_STAGE_H

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

typedef struct executed_instruction {
    // TO BE FIXED
    // R-format: opcode + destination + value
    // I-format: opcode + destination + value
    //          store: opcode + stored_value + value
    // J-format: opcode + value
    
    char opcode; // opcode of the instruction
    char destination;
    uint32_t stored_value; // signed?
    uint32_t value;
} executed_instruction;

class WritebackStage {
 private:
	uint32_t* pc;
	uint32_t* registers;
	//pending registers?

 public:
    bool noop;
    executed_instruction executed;

    WritebackStage(uint32_t* registers);
	void tick();
};
#endif /* WRITEBACK_STAGE_H */
