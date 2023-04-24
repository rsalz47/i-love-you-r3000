#include <iostream>
#include "execute_stage.h"

ExecuteStage::ExecuteStage(MemoryStage &m_s) : memory_stage(m_s) {}

// In one clock tick, execute executes the instruction that decode has decoded.

void ExecuteStage::reset() {
    noop = true;
    blocked = false;
}

void ExecuteStage::tick() {
    if (noop) {
        std::cout << "Execute: No instruction delivered by decode, idle for this cycle..." << std::endl;
        if (!memory_stage.blocked) {
            memory_stage.noop = true;
        }
        return;
    }
    if (!blocked) {
        std::cout << "Execute: Decode has delivered an instruction, now executing... \n";
        // execute an instruction
        std::cout << "Execute: Executing instruction with opcode " << static_cast<int>(decoded.opcode) << std::endl;
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
            executed.value = static_cast<int32_t>(decoded.operand_1) + static_cast<int32_t>(decoded.addr_or_imm); // sign extended
            executed.dest_value = decoded.dest_value;
            break;
        }
        case 0b100000:   // lw
            // address computation
            executed.value = static_cast<int32_t>(decoded.operand_1) + static_cast<int32_t>(decoded.addr_or_imm);
            break;
        case 0b100001:  // li
            executed.value = static_cast<int32_t>(decoded.addr_or_imm);
            break;
        case 0b100010: { //b
            executed.branch_taken = true;
            executed.addr = decoded.addr_or_imm;
            break;
        }
        case 0b100011: { // beq
            executed.branch_taken = (static_cast<int32_t>(decoded.dest_value) == static_cast<int32_t>(decoded.operand_1));
            executed.addr = decoded.addr_or_imm;
            break;
        }
        case 0b100100: { // bne
            executed.branch_taken = (static_cast<int32_t>(decoded.dest_value) != static_cast<int32_t>(decoded.operand_1));
            executed.addr = decoded.addr_or_imm;            
            break;
        }
        case 0b100111: { // bgt
            executed.branch_taken = (static_cast<int32_t>(decoded.dest_value) > static_cast<int32_t>(decoded.operand_1));
            executed.addr = decoded.addr_or_imm;            
            break;
        }
        case 0b101000: { // blt
            executed.branch_taken = (static_cast<int32_t>(decoded.dest_value) < static_cast<int32_t>(decoded.operand_1));
            executed.addr = decoded.addr_or_imm;
            break;
        }
        case 0b101111: // j
            executed.addr = decoded.target_addr;
            break;
    }
        std::cout << "Finished executing the instruction with opcode " << static_cast<int>(decoded.opcode) << " and value " << executed.value << std::endl; 
    }
    if (!memory_stage.blocked) { // memory stage not blocked, pass the executed instruction
        std::cout << "Execute: Delivering instruction to Memory..." << std::endl;
        memory_stage.executed = executed;
        memory_stage.noop = false;
        blocked = false;
    } else {
        blocked = true;
    }
}
