#include "writeback_stage.h"

WritebackStage::WritebackStage(uint32_t* registers) : registers(registers) {}

void WritebackStage::tick() {
    if (noop) {
        return;
    }

    // R-format + lw + li need writeback, sw does not need writeback
    if (executed.opcode <= 0b010110 || executed.opcode == 0b100000 || executed.opcode == 0b100001) { 
        registers[executed.destination] = executed.value;
    }
        
    // TODO branching
    // deal with dependencies
}
