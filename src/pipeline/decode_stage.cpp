#include "decode_stage.h"

DecodeStage::DecodeStage(ExecuteStage &e, uint32_t* registers) : execute_stage(e), registers(registers) {}

// In one tick of the decode stage, we decode one instruction 
// as long as the stage is not currently blocked.
void DecodeStage::tick() {
    std::cout << "Decode: Current instruction: " << encoded_instruction << std::endl;
    if(encoded_instruction == 0x0) {
        std::cout << "Decode: Cannot decode an instruction, because Fetch has not delivered an instruction. Idle for this cycle..." << std::endl;
        return;
    }
    // only decode an instruction if we ourselves are not blocked
    else if(!blocked) {
        std::cout << "Decode: Fetch has delivered an instruction, now decoding " << encoded_instruction << std::endl;
        uint32_t instr = encoded_instruction;
        uint32_t encoded_op = (instr >> 26) & 0b111111;        
        switch(encoded_op) {
        case 0b000000:
            decoded.operation = "add";
            break;
        case 0b000001:
            decoded.operation = "sub";
            break;
        case 0b000010:
            decoded.operation = "mul";
            break;
        case 0b000011:
            decoded.operation = "div";
            break;
        case 0b011111:
            decoded.operation = "sw";
            break;
        case 0b100000:
            decoded.operation = "lw";
            break;
        case 0b100001:
            decoded.operation = "li";
            break;
        case 0b100011: // opcode following assembler.h
            decoded.operation = "beq";
            break;
        case 0b100100:
            decoded.operation = "bne";
            break;
        case 0b100111:
            decoded.operation = "bgt";
            break;
        case 0b101000:
            decoded.operation = "blt";
            break;
        }

        decoded.opcode = encoded_op;
        if (encoded_op <= 0b010110 && encoded_op >= 0b000000) { // R-format
            // need to check dependencies
            decoded.destination = (instr >> 21) & 0b11111;
            decoded.operand_1 = registers[(instr >> 16) & 0b11111];
            decoded.operand_2 = registers[(instr >> 11) & 0b11111];
            decoded.shamt = (instr >> 6) & 0b11111;
        } else if (encoded_op >= 0b010111 && encoded_op <= 0b101110) { //I-format
            // need to check dependencies
            std::cout << "Decode: I-format" << std::endl;
            decoded.destination = (instr >> 21) & 0b11111;
            decoded.operand_1 = registers[(instr >> 16) & 0b11111];
            decoded.addr_or_imm = instr & 0xFFFF;

            // for sw, need to obtain the value stored in the dest register as well
            // may need to do this for other instructions
            if (encoded_op == 0b011111) { // sw
                decoded.dest_value = registers[decoded.destination];
            } else if (encoded_op == 0b100011 || encoded_op == 0b100100 || encoded_op == 0b100111 || encoded_op == 0b101000) { //beq, bne, bgt, blt 
                decoded.dest_value = registers[decoded.destination];
            }
        } else if (encoded_op >= 0b101111 && encoded_op <= 0b111111) { // J-format
            if (encoded_op == 0b101111) {
                decoded.target_addr = instr & 0x3FFFFFF;
            }
            // TODO: jal, nop, hcf
        }            
        std::cout << "Decode: Finished decoding an instruction of type " << decoded.operation << std::endl;
    }

    std::cout << "Decode: Attempting to deliver instruction of type " << decoded.operation << " to Execute." << std::endl;
    // if execute is blocked, then we cannot pass data forward.
    if(execute_stage.blocked) {
        std::cout << "Decode: Cannot deliver instruction to Execute because Execute is blocked. Blocking." << std::endl;
        blocked = true;
    }
    else {
        execute_stage.decoded = decoded;
        std::cout << "Decode: destination: " << static_cast<int>(decoded.destination) << std::endl;
        execute_stage.noop = false;
        std::cout << "Decode: Delivered instruction to Execute." << std::endl;
        blocked = false;
    }
}
