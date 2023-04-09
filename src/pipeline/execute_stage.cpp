#include "execute_stage.h"

ExecuteStage::ExecuteStage(MemoryStage &m_s) : memory_stage(m_s) {}

// In one clock tick, execute executes the instruction that decode has decoded.
void ExecuteStage::tick() {
    // execute an instruction 
}
