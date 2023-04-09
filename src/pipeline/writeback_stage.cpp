#include "writeback_stage.h"

void WritebackStage::tick() {
    if (noop) {
        return;
    }
        
    // if instruction has branch, update PC
    //TODO: if JSR, update PC and return reg
    if (branch) {
        *pc = value;
        return;
    }

    if (!writeback) {
        // deal with dependencies
        return;
    }

    // the instruction needs to writeback
    // write to register
    registers[reg] = value;
    // deal with dependencies

}

