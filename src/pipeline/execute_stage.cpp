#include "execute_stage.h"

ExecuteStage::ExecuteStage(MemoryStage &m_s) : memory_stage(m_s) {}

// In one clock tick, execute executes the instruction that decode has decoded.
void ExecuteStage::tick() {
    if (!blocked) {
        // execute an instruction
        executed.opcode = decoded.opcode;
        executed.destination = decoded.destination;
        switch(executed.opcode) {
        case 0b000000:  // add
            executed.value = static_cast<int32_t>(decoded.operand_1) + static_cast<int32_t>(decoded.operand_2);
            break;
        case 0b000001:  // sub
            executed.value = static_cast<int32_t>(decoded.operand_1) - static_cast<int32_t>(decoded.operand_2);
            break;
        case 0b000010:  // mul
            executed.value = static_cast<int32_t>(decoded.operand_1) * static_cast<int32_t>(decoded.operand_2);
            break;
        case 0b000011:  // div
            executed.value = static_cast<int32_t>(decoded.operand_1) / static_cast<int32_t>(decoded.operand_2);
            break;
        case 0b011111: { // sw
            // address computation
            executed.value = static_cast<int32_t>(decoded.operand_1) + static_cast<int32_t>(decoded.addr_or_imm);
            executed.stored_value = decoded.stored_value;
            break;
        }
        case 0b100000:   // lw
            // address computation
            executed.value = static_cast<int32_t>(decoded.operand_1) + static_cast<int32_t>(decoded.addr_or_imm);
            break;
        case 0b100001:  // li
            executed.value = static_cast<int32_t>(decoded.operand_1);
            break;
            // branch
        }
    }
    if (!memory_stage.blocked) { // memory stage not blocked, pass the executed instruction
        memory_stage.executed = executed;
        blocked = false;
    } else {
        blocked = true;
    }
}
