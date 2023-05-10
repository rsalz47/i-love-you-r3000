#include <iostream>
#include "writeback_stage.h"
#include <bitset>
#include <vector>

WritebackStage::WritebackStage(uint32_t* regs, uint32_t* program_counter, std::vector<int> &dependency_list):
                               registers(regs), 
                               pc(program_counter),
                               dependency_list(dependency_list){}

void WritebackStage::reset() {
    noop = true;
    squashed = false;
    exit = false;
    writeback_finished = false;
}

void WritebackStage::tick() {
    squashed = false;
    if (noop) {
        return;
    }
    writeback_finished = true;
    // R-format + lw + li need writeback, sw does not need writeback
    if (executed.opcode == 0b110001) { //nop
        return;
    } else if (executed.opcode == 0b111111) { //hcf
        exit = true;
    } else if (executed.opcode <= 0b11110 || executed.opcode == 0b100000 || executed.opcode == 0b100001){        
        registers[executed.destination] = executed.value;
        dependency_list.erase(dependency_list.begin());

    } else if ((executed.opcode <= 0b101110 && executed.opcode >= 0b100010) || executed.opcode == 0b101111) { //branch + unconditional jump
        if (executed.branch_taken || executed.opcode == 0b101111) {
            // if branch taken squash all the previous stages
            squashed = true;
            *pc = executed.addr;
        }
        // branching not taken, do nothing
        noop = true;
    }
        
    // deal with dependencies
}
