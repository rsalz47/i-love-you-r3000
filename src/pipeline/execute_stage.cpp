#include <iostream>
#include "execute_stage.h"

ExecuteStage::ExecuteStage(MemoryStage &m_s) : memory_stage(m_s) {}

// In one clock tick, execute executes the instruction that decode has decoded.
void ExecuteStage::tick() {
    if (noop) {
        return;
    }
    if (!blocked) {
        std::cout << "Execute: Decode has delivered an instruction, now executing... \n";
        // execute an instruction
        std::cout << "Execute: Opcode: " << static_cast<int>(decoded.opcode) << std::endl;
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
        std::cout << "Finished executing the instruction, opcode: " << decoded.opcode << " destination: " << executed.destination << " value: " << executed.value << std::endl; 
    }
    if (!memory_stage.blocked) { // memory stage not blocked, pass the executed instruction
        std::cout << "Delivering instruction to memory" << std::endl;
        memory_stage.executed = executed;
        memory_stage.noop = false;
        blocked = false;
    } else {
        blocked = true;
    }
}
