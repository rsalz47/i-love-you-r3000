#ifndef DECODE_STAGE_H
#define DECODE_STAGE_H

// The decode stage takes the fetched instruction from 
// the fetch stage and decodes it (essentially translates it back into asm)
// This will largely be a giant switch case

// This has to contain all possible fields you can parse out of an instruction
#include <iostream>
#include "execute_stage.h"

class DecodeStage {
 private: 
    ExecuteStage &execute_stage;
    uint32_t* registers;
 public:
    bool blocked = false;
    bool noop = true;
    uint32_t encoded_instruction = 0x0;
    decoded_instruction decoded;
    
    DecodeStage(ExecuteStage &e, uint32_t *registers);

    // In one tick of the decode stage, we decode one instruction 
    // as long as the stage is not currently blocked.
    void tick();
};
#endif /* DECODE_STAGE_H */
