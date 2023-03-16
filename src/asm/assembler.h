#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <map>
#include <string>
#include <vector>

enum InstructionFormat {R, I, J};


namespace RFormat {
    inline std::map<std::string, unsigned long> RTypes {
        {"add",  0b000000},
        {"sub",  0b000001},
        {"mul",  0b000010},
        {"div",  0b000011},
        {"sll",  0b000100},
        {"sllv", 0b000101},
        {"srl",  0b000110},
        {"srlv", 0b000111},
        {"sra",  0b001000},
        {"srav", 0b001001},
        {"and",  0b001010},
        {"or",   0b001011},
        {"xor",  0b001100},
        {"nor",  0b001101},
        {"jr",   0b001110},
        {"jral", 0b001111},
        {"move", 0b010000},
        {"seq",  0b010001},
        {"sge",  0b010010},
        {"sgt",  0b010011},
        {"sle",  0b010100},
        {"slt",  0b010101},
        {"sne",  0b010110}
    };

    inline unsigned long pack_rd(unsigned long rd) {
        return (rd & 0x1F) << 11;
    }

    inline unsigned long pack_shamt(unsigned long shamt) {
        return (shamt & 0x1F) << 6;
    }

    inline unsigned long pack_funct(unsigned long funct) {
        return funct & 0x3F;
    }
}

inline namespace IFormat {
    inline std::map<std::string, unsigned long> ITypes {
        {"addi",  0b010111},
        {"subi",  0b011000},
        {"muli",  0b011001},
        {"divi",  0b011010},
        {"slti",  0b011011},
        {"andi",  0b011100},
        {"ori",   0b011101},
        {"xori",  0b011110},
        {"sw",    0b011111},
        {"lw",    0b100000},
        {"li",    0b100001},
        {"b",     0b100010},
        {"beq",   0b100011},
        {"bne",   0b100100},
        {"beqz",  0b100101},
        {"bnez",  0b100110},
        {"bgt",   0b100111},
        {"blt",   0b101000},
        {"bgtz",  0b101001},
        {"bltz",  0b101010},
        {"bgte",  0b101011},
        {"blte",  0b101100},
        {"bgtez", 0b101101},
        {"bltez", 0b101110}
    };

    inline unsigned long pack_addr_imm(unsigned long addr_or_imm) {
        return addr_or_imm & 0xFF;
    }
}

inline namespace JFormat {
    inline std::map<std::string, unsigned long> JTypes {
        {"j",   0b101111},
        {"jal", 0b110000},
        {"nop", 0b110001},
        {"hcf", 0b111111}
    };

    inline unsigned long pack_target_addr(unsigned long target_addr) {
        return target_addr & 0x3FFFFFF;
    }
}

inline int format_of(std::string op) {
    if(RFormat::RTypes.count(op))
        return R;
    if(IFormat::ITypes.count(op))
        return I;
    if(JFormat::JTypes.count(op))
        return J;
    return -1;
}

inline unsigned long pack_opcode(unsigned long op) {
    return (op & 0x3F) << 26;
}

inline unsigned long pack_rs(unsigned long rs) {
    return (rs & 0x1F) << 21;
}

inline unsigned long pack_rt(unsigned long rt) {
    return (rt & 0x1F) << 16;
}

unsigned long make_r_type(std::vector<std::string> tokens);
unsigned long make_j_type(std::vector<std::string> tokens);
unsigned long make_i_type(std::vector<std::string> tokens);
unsigned long build_instruction(std::string instr);

#endif
