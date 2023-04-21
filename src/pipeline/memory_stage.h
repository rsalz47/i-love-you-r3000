#ifndef MEMORY_STAGE_H
#define MEMORY_STAGE_H

#include "writeback_stage.h"
#include "../mem/memory_system.h"

class MemoryStage {
 private:
    MemorySystem* mem_sys;

 public:
    WritebackStage &wb_stage;
    bool blocked = false;
    executed_instruction executed;
    bool noop = true;

    MemoryStage(WritebackStage& wb_stage, MemorySystem* ms);
    
    void reset(); 
    void tick();

    void set_mem_sys(MemorySystem* mem_sys);        
};
#endif /* MEMORY_STAGE_H */
