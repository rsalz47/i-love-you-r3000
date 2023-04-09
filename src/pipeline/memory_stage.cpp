#include "memory_stage.h"

MemoryStage::MemoryStage(WritebackStage &wb_stage, Cache* cache):
    wb_stage(wb_stage), cache(cache) {}
    
void MemoryStage::tick() {
    if (noop) {
        return;
    }
    // if not mem and writeback, pass the instruction (reg + value) to wb
    if (decoded.operation != "sw" || decoded.operation != "lw") {
        // add, sub, mul, div, li all require writeback
        wb_stage.writeback = true;
        wb_stage.reg = decoded.destination;
        wb_stage.value = decoded.target_addr;
        return;
    }

    /**
    if (decoded.operation == "sw") {
        //TODO need to modify the arguments in the future
        uint32_t* data = cache->store(addr, value, 4); // memory stage id = 4
        if (data == nullptr) {
            wb_stage->noop = true;
            blocked = true;
        } else {
            // for a store, writeback does not need to do anything?
            wb_stage->noop = true;
            wb_stage->writeback = false;
            blocked = false;
        }
    } else { // load
        //TODO need to modify the arguments in the future
        uint32_t* result = cache->load(addr, cache->store(addr, 4));
        if (result == nullptr) {
            wb_stage->noop = true;
            blocked = true;
        } else {
            wb_stage->noop = false;
            wb_stage->writeback = true;
            wb_stage->reg = reg;
            wb_stage->value = *result;                    
            blocked = false;
        }                                               
    }
    **/
}
