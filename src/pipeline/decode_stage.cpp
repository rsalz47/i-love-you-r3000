#include "decode_stage.h"
#include <algorithm>

DecodeStage::DecodeStage(ExecuteStage &e, uint32_t* registers, std::vector<int> &dependency_list) : execute_stage(e), 
                         registers(registers), 
                         dependency_list(dependency_list) {}

// In one tick of the decode stage, we decode one instruction 
// as long as the stage is not currently blocked.

void DecodeStage::reset() {
    noop = true;
    blocked = false;
    encoded_instruction = 0x0;
    dependency_list.clear();
}  

bool DecodeStage::check_dependency_issue(int reg) {
    return std::find(dependency_list.begin(),
                     dependency_list.end(),
                     reg) != dependency_list.end();
}

void DecodeStage::tick() {
    if(encoded_instruction == 0x0 || noop) {
        std::cout << "Decode: No instruction delivered by Fetch, or this instruction is a noop. Idle for this cycle..." << std::endl;
        // if current instruction is a noop and the next stage is not blocked
        // need to pass the noop to the next stage
        if (noop && !execute_stage.blocked) {
            execute_stage.noop = true;
        }
        return;
    }

    // We can be blocked for one of two reasons, see below
    bool next_stage_blocked;
    bool dependency_issue;

    next_stage_blocked = execute_stage.blocked;
    
    dependency_issue = check_dependency_issue((encoded_instruction >> 21) & 0b11111) ||
                       check_dependency_issue((encoded_instruction >> 16) & 0b11111) || 
                       check_dependency_issue((encoded_instruction >> 11) & 0b11111);     

    blocked = (next_stage_blocked || dependency_issue);
    // only decode an instruction if we ourselves are not blocked
    if(!blocked) {
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
            case 0b101111:
                decoded.operation = "j";
                break;
            case 0b110001:
                decoded.operation = "nop";
                break;
            case 0b111111:
                decoded.operation = "hcf";
                break;
        }

        decoded.opcode = encoded_op;
        if (encoded_op <= 0b010110 && encoded_op >= 0b000000) { // R-format
            decoded.destination = (instr >> 21) & 0b11111;
            decoded.operand_1 = registers[(instr >> 16) & 0b11111];
            decoded.operand_2 = registers[(instr >> 11) & 0b11111];
            decoded.shamt = (instr >> 6) & 0b11111;
            
            // Since this is an aRithmetic type instruction, we will be writing to the destination register
            // as such, the destination register should be placed on the dependency list

            // For WHATEVER REASON :))) JR and JRAL are R-Format instructions
            // They do not need this dependency behavior, and this if-condition excludes them
            if(encoded_op != 0b001110 && encoded_op != 0b001111) {
                dependency_list.push_back(decoded.destination);
            }

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

            // BRANCH and STORE instructions do not have a return register,
            // and this if-condition makes it so that we do not accidentally
            // push anything related to them to the dependency list
            if(encoded_op < 0b100010 && encoded_op != 0b011111) {
                std::cout << "Decode: Adding dest register to the dependency list... " << std::endl;
                dependency_list.push_back(decoded.destination);
                std::cout << "Decode: Dest register added. Opcode: " << encoded_op << " The dependency list currently has "
                          << dependency_list.size() << " elements" << std::endl;
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
    else if (dependency_issue) {
        std::cout << "Decode: Cannot deliver instruction to Execute beacuse of dependency issues. Blocking." << std::endl;
        blocked = true;
        execute_stage.noop = true;
    }
    else {
        execute_stage.decoded = decoded;
        std::cout << "Decode: destination: " << static_cast<int>(decoded.destination) << std::endl;
        execute_stage.noop = false;
        std::cout << "Decode: Delivered instruction to Execute." << std::endl;
        blocked = false;
    }
}
