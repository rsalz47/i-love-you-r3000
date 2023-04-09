#ifndef MEMORY_STAGE_H
#define MEMORY_STAGE_H

#include "writeback_stage.h"
#include "../mem/cache.h"

class MemoryStage {
 private:
    WritebackStage &wb_stage;
    Cache* cache;

 public:
    bool blocked = false;
    executed_instruction executed;
    bool noop = true;

    MemoryStage(WritebackStage& wb_stage, Cache* cache);
    
    void tick();
        
};
#endif /* MEMORY_STAGE_H */
