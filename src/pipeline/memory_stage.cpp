#include <iostream>
#include "memory_stage.h"

MemoryStage::MemoryStage(WritebackStage &wb_stage, MemorySystem* ms):
    wb_stage(wb_stage), mem_sys(ms) {}
    
void MemoryStage::reset() {
    blocked = false;
    noop = true;    
    // not resetting executed_instruction because there's no reason to 
    mem_sys->reset_delay();
}

void MemoryStage::set_mem_sys(MemorySystem* mem_sys) {
    this->mem_sys = mem_sys;
}


void MemoryStage::tick() {
    if (noop) {
        std::cout << "Memory: No instruction delivered by Execute, idle for this cycle..." << std::endl;
        // next stage should be noop as well
        wb_stage.noop = true;
        return;
    }
    if (!blocked) { // if not blocked, process next instruction
        std::cout << "Memory: not blocked" << std::endl;
        // if not mem and writeback, pass the instruction (reg + value) to wb
        if (executed.opcode != 0b011111 && executed.opcode != 0b100000) {
            // not memory access instruction
            std::cout << "Memory: Delivered instructions with dest " << executed.destination << " to writeback stage" << std::endl;
            std::cout << "dest: " << executed.destination << std::endl;
            wb_stage.executed = executed;
            wb_stage.noop = false;
            return;
        }

        if (executed.opcode == 0b011111) { // sw
            std::cout << "Memory: Execute has delivered a store instruction... \n";
            // store: opcode stored_value(data) value(addr)
            uint32_t* data = mem_sys->store(executed.value, executed.dest_value, 4); // memory stage id = 4
            if (data == nullptr) {
                std::cout << "Memory: store blocked\n";
                wb_stage.noop = true;
                blocked = true;
            } else {
                // for a store, writeback does not need to do anything
                // need to pop the register out of the pending registers vector
                std::cout << "Memory: store finished\n";
                wb_stage.noop = false;
                wb_stage.executed = executed;
                blocked = false;
            }
        } else { //lw
            std::cout << "Memory: Execute has delivered a load instruction... \n";
            uint32_t* result = mem_sys->load(executed.value, 4);
            if (result == nullptr) {
                std::cout << "Memory: Load blocked\n";
                wb_stage.noop = true;
                blocked = true;
            } else {
                std::cout << "Memory: Load finished. The value loaded is " << *result << std::endl;
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
            uint32_t* data = mem_sys->store(executed.value, executed.dest_value, 4); // memory stage id = 4
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
            uint32_t* result = mem_sys->load(executed.value, 4);
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
