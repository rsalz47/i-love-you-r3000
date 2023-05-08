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
    std::cout << std::endl;
    squashed = false;
    std::cout << "Writeback: Current dependency list has " << dependency_list.size() << " elements." << std::endl;
    for (unsigned int i = 0; i < dependency_list.size(); ++i) {
        std::cout << dependency_list[i] << " ";
    }
    std::cout << std::endl;
    if (noop) {
        std::cout << "Writeback: No instruction to execute, Idle for this cycle..." << std::endl;
        return;
    }
    std::cout << "Writeback: current opcode: " << static_cast<int>(executed.opcode) << std::endl;
    writeback_finished = true;
    // R-format + lw + li need writeback, sw does not need writeback
    if (executed.opcode == 0b110001) { //nop
        std::cout << "Writeback: Current instruction is nop, do nothing... " << std::endl;
        return;
    } else if (executed.opcode == 0b111111) { //hcf
        exit = true;
        std::cout << "Writeback: Current instruction is hcf, exiting... " << std::endl;
    } else if (executed.opcode <= 0b11110 || executed.opcode == 0b100000 || executed.opcode == 0b100001){        
        registers[executed.destination] = executed.value;
        std::cout << "Writeback: Current instruction needs writeback. Writing to Registers..." << std::endl;

        std::cout << "Writeback: Current dependency list has " << dependency_list.size() << " elements" << std::endl;
        dependency_list.erase(dependency_list.begin());
        std::cout << "Writeback: Dest register removed from the dependency list" << std::endl;

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
        
    // deal with dependencies
}
