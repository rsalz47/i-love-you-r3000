#ifndef MEMORY_STAGE_H
#define MEMORY_STAGE_H

#include "writeback_stage.h"
#include "../mem/cache.h"

typedef struct decoded_instruction {
    std::string operation;
    uint32_t operand_1; // src1
    uint32_t operand_2; // src2
    char destination; // dest
    char shamt; // shift amount
    uint32_t addr_or_imm;
    uint32_t target_addr;
} decoded_instruction;

class MemoryStage {
 private:
    WritebackStage wb_stage;
    Cache* cache;

 public:
    bool blocked = false;
    decoded_instruction decoded;
    bool noop = true;

    MemoryStage(WritebackStage& wb_stage, Cache* cache);
    
    void tick();
        
};
#endif /* MEMORY_STAGE_H */
