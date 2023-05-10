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
        if (!memory_stage.blocked) {
            memory_stage.noop = true;
        }
        return;
    }
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
        case 0b000100: { // sll
            executed.value = decoded.operand_1 << decoded.shamt;
            break;
        }
        case 0b000101: { // sllv
            executed.value = decoded.operand_1 << decoded.operand_2;
            break;
        }
        case 0b000110: { // srl
            executed.value = decoded.operand_1 >> decoded.shamt;
            break;
        }
        case 0b000111: { // srlv
            executed.value = decoded.operand_1 >> decoded.operand_2;
            break;
        }
        case 0b001000: { // sra
            executed.value = static_cast<int32_t>(decoded.operand_1) >> decoded.shamt;
            break;
        }
        case 0b001001: { // srav
            executed.value = static_cast<int32_t>(decoded.operand_1) >> decoded.operand_2;
            break;
        }
        case 0b011111: { // sw
            // address computation
            executed.value = static_cast<int32_t>(decoded.operand_1) + static_cast<int32_t>(decoded.addr_or_imm); // sign extended
            executed.dest_value = decoded.dest_value;
            break;
        }
        case 0b001010: { // and
            executed.value = decoded.operand_1 & decoded.operand_2;
            break;
        }
        case 0b001011: { // or
            executed.value = decoded.operand_1 | decoded.operand_2;
            break;
        }
        case 0b001100: { // xor
            executed.value = decoded.operand_1 ^ decoded.operand_2;
            break;
        }
        case 0b001101: { // nor
            executed.value = ~ (decoded.operand_1 | decoded.operand_2);
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
        case 0b010111: { // addi
            executed.value = static_cast<int32_t>(decoded.operand_1) + static_cast<int32_t>(decoded.addr_or_imm);
            break;
        }
        case 0b011000: { // subi
            executed.value = static_cast<int32_t>(decoded.operand_1) - static_cast<int32_t>(decoded.addr_or_imm);
            break;
        }
        case 0b011001: { // muli
            executed.value = static_cast<int32_t>(decoded.operand_1) * static_cast<int32_t>(decoded.addr_or_imm);
            break;
        }
        case 0b011010: { // divi
            executed.value = static_cast<int32_t>(decoded.operand_1) / static_cast<int32_t>(decoded.addr_or_imm);
            break;
        }
        case 0b011011: { // slti
            if (static_cast<int32_t>(decoded.operand_1) < static_cast<int32_t>(decoded.addr_or_imm)) {
                executed.value = 1;
            }
            else {
                executed.value = 0;
            }
            break;
        }
        case 0b011100: { // andi
            executed.value = decoded.operand_1 & decoded.addr_or_imm;
            break;
        }
        case 0b011101: { // ori
            executed.value = decoded.operand_1 | decoded.addr_or_imm;
            break;
        }
        case 0b011110: { // xori
            executed.value = decoded.operand_1 ^ decoded.addr_or_imm;
            break;
        }                        
        case 0b101111: // j
            executed.addr = decoded.target_addr;
            break;
    }

    }
    if (!memory_stage.blocked) { // memory stage not blocked, pass the executed instruction
        memory_stage.executed = executed;
        memory_stage.noop = false;
        blocked = false;
    } else {
        blocked = true;
    }
}
