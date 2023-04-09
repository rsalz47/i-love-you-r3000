// The decode stage takes the fetched instruction from 
// the fetch stage and decodes it (essentially translates it back into asm)
// This will largely be a giant switch case

// This has to contain all possible fields you can parse out of an instruction
#include <iostream>

typedef struct decoded_instruction {
    std::string operation;
    uint32_t operand_1; // src1
    uint32_t operand_2; // src2
    char destination; // dest
    char shamt; // shift amount
    uint32_t addr_or_imm;
    uint32_t target_addr;
} decoded_instruction;

class DecodeStage {
    private: 
        ExecuteStage execute_stage;
    public:
        bool blocked = false;
        uint32_t encoded_instruction = 0x0;
        decoded_instruction decoded;
    
    DecodeStage(ExecuteStage e) {
       execute_stage = e;
    }

    // In one tick of the decode stage, we decode one instruction 
    // as long as the stage is not currently blocked.
    void tick() {
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
           execute_stage.decoded_instruction = decoded;
           std::cout << "Decode: Delivered instruction to Execute." << std::endl;
           blocked = false;
        }
    }
};
