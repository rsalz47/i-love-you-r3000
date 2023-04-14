#include <iostream>
#include "writeback_stage.h"
#include <bitset>

WritebackStage::WritebackStage(uint32_t* regs, uint32_t* program_counter):registers(regs), pc(program_counter){}

void WritebackStage::tick() {
    std::cout << std::endl;
    squashed = false;
    if (noop) {
        std::cout << "Writeback: No instruction to execute, Idle for this cycle..." << std::endl;
        return;
    }
    std::cout << "Writeback: current opcode: " << static_cast<int>(executed.opcode) << std::endl;

    // R-format + lw + li need writeback, sw does not need writeback
    if (executed.opcode <= 0b010110 || executed.opcode == 0b100000 || executed.opcode == 0b100001) {        
        registers[executed.destination] = executed.value;
        std::cout << "Writeback: Current instruction needs writeback. Writing to Registers..." << std::endl;
    } else if ((executed.opcode <= 0b101110 && executed.opcode >= 0b100010) || executed.opcode == 0b101111) { //branch + unconditional jump
        std::cout << "Writeback: Current instruction is a branch or jump. May need to squash." << std::endl;
        std::cout << "Writeback: Opcode of potentially squashing instruction is: " << std::bitset<32>(executed.opcode) << std::endl;
        if (executed.branch_taken || executed.opcode == 0b101111) {
            // if branch taken squash all the previous stages
            squashed = true;
            std::cout << "Writeback: Jump or branch taken. Issuing signal to squash the pipeline." << std::endl;
            *pc = executed.addr;
        }
        // branching not taken, do nothing
        noop = true;
    }
        
    // TODO branching
    // deal with dependencies
}
