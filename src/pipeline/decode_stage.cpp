#include "decode_stage.h"

DecodeStage::DecodeStage(ExecuteStage &e) : execute_stage(e) {}

// In one tick of the decode stage, we decode one instruction 
// as long as the stage is not currently blocked.
void DecodeStage::tick() {
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
            // case branch:
        }

        decoded.destination = (instr >> 21) & 0b11111;
        decoded.operand_1 = (instr >> 16) & 0b11111;
        decoded.operand_2 = (instr >> 11) & 0b11111;
        decoded.shamt = (instr >> 6) & 0b11111;

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
        std::cout << "Decode: Delivered instruction to Execute." << std::endl;
        blocked = false;
    }
}
