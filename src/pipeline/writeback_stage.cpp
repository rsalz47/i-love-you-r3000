#include <iostream>
#include "writeback_stage.h"

WritebackStage::WritebackStage(uint32_t* regs, uint32_t* program_counter):registers(regs), pc(program_counter){}

void WritebackStage::tick() {
    squashed = false;
    if (noop) {
        return;
    }
    std::cout << "WB: current opcode: " << static_cast<int>(executed.opcode) << std::endl;
    // R-format + lw + li need writeback, sw does not need writeback
    if (executed.opcode <= 0b010110 || executed.opcode == 0b100000 || executed.opcode == 0b100001) {        
        registers[executed.destination] = executed.value;
        std::cout << "Writeback: current instruction needs writeback\n";
    } else if (executed.opcode <= 0b101110 && executed.opcode >= 0b100010) { //branch
        std::cout << "Writeback: Current instruction is a branch" << std::endl;
        if (executed.branch_taken) {
            // if branch taken squash all the previous stages
            squashed = true;
            *pc = executed.addr;
        }
        // branching not taken, do nothing
    }
        
    // TODO branching
    // deal with dependencies
}
