#include "memory_stage.h"

MemoryStage::MemoryStage(WritebackStage &wb_stage, Cache* cache):
    wb_stage(wb_stage), cache(cache) {}
    
void MemoryStage::tick() {
    if (!blocked) { // if not blocked, process next instruction
        // if not mem and writeback, pass the instruction (reg + value) to wb
        if (executed.opcode != 0b011111 && executed.opcode != 0b100000) { // not memory access instruction
            // add, sub, mul, div, li all require writeback
            wb_stage.executed = executed;
            return;
        }

        if (executed.opcode == 0b011111) { // sw
            // store: opcode stored_value(data) value(addr)
            uint32_t* data = cache->store(executed.value, executed.stored_value, 4); // memory stage id = 4
            if (data == nullptr) {
                wb_stage.noop = true;
                blocked = true;
            } else {
                // for a store, writeback does not need to do anything
                // need to pop the register out of the pending registers vector
                wb_stage.noop = false;
                wb_stage.executed = executed;
                blocked = false;
            }
        } else { //lw
            uint32_t* result = cache->load(executed.value, 4);
            if (result == nullptr) {
                wb_stage.noop = true;
                blocked = true;
            } else {
                wb_stage.noop = false;
                wb_stage.executed = executed;
                wb_stage.executed.value = *result;
                blocked = false;
            }                                               
        }
    } else {
        // blocked, requst memory access again
        if (executed.opcode == 0b011111) { // sw
            // store: opcode stored_value(data) value(addr)
            uint32_t* data = cache->store(executed.value, executed.stored_value, 4); // memory stage id = 4
            if (data == nullptr) {
                wb_stage.noop = true;
                blocked = true;
            } else {
                // for a store, writeback does not need to do anything
                // need to pop the register out of the pending registers vector
                wb_stage.noop = false;
                wb_stage.executed = executed;
                blocked = false;
            }
        } else { //lw
            uint32_t* result = cache->load(executed.value, 4);
            if (result == nullptr) {
                wb_stage.noop = true;
                blocked = true;
            } else {
                wb_stage.noop = false;
                wb_stage.executed = executed;
                wb_stage.executed.value = *result;
                blocked = false;
            }
        }
    }
}
