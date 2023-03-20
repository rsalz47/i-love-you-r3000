#include <sstream>
#include <iostream>
#include <fstream> 
#include <vector>
#include <bitset>

#include "assembler.h"
#include "../mem/registers.h"

using namespace std;

unsigned long make_r_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = RFormat::RTypes[op];

    if(op == "add") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(Registers[tokens[1]]);
        instruction |= pack_rt(Registers[tokens[2]]);
        instruction |= RFormat::pack_rd(Registers[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);

    }
    else if(op == "sub") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "mul") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "div") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sll") {
        return opc; 
    }
    else if(op == "sllv") {
        return opc; 
    }
    else if(op == "slr") {
        return opc; 
    }
    else if(op == "slrv") {
        return opc; 
    }
    else if(op == "sra") {
        return opc; 
    }
    else if(op == "srav") {
        return opc; 
    }
    else if(op == "and") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "or") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "xor") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "nor") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "jr") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
    }
    else if(op == "jral") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
    }
    else if(op == "move") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
    }
    else if(op == "seq") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sge") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sgt") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sle") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "slt") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sne") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= RFormat::pack_rd(Registers[tokens[3]]);
        instruction &= RFormat::pack_shamt((unsigned long) 0x0);
        instruction &= RFormat::pack_funct((unsigned long) 0x0);
    }
    cout << bitset<32>(instruction) << endl;
    return instruction;
}

unsigned long make_i_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = IFormat::ITypes[op];

    if(op == "addi") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "subi") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "muli") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "divi") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "slti") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "andi") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "ori") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "xori") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "sw") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "lw") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "li") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[2]));
    }
    else if(op == "b") {
        instruction &= pack_opcode(opc);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[1]));
    }
    else if(op == "beq") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bne") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bgt") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "blt") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bgtz") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bltz") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bgte") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "blte") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bgtez") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bltez") {
        instruction &= pack_opcode(opc);
        instruction &= pack_rs(Registers[tokens[1]]);
        instruction &= pack_rt(Registers[tokens[2]]);
        instruction &= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    cout << bitset<32>(instruction) << endl;
    return instruction;
}

unsigned long make_j_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = JFormat::JTypes[op];

    if(op == "j") {
        instruction &= pack_opcode(opc);
        instruction &= JFormat::pack_target_addr(stoul(tokens[1]));
    }
    else if(op == "jal") {
        instruction &= pack_opcode(opc);
        instruction &= JFormat::pack_target_addr(stoul(tokens[1]));
    }
    else if(op == "nop") {
        return opc; 
    }
    else if(op == "hcf") {
        return opc; 
    }
    cout << bitset<32>(instruction) << endl;
    return instruction;
}

unsigned long build_instruction(string instr) {
	// Tokenize instruction
	vector<string> tokens;
	stringstream inst(instr);
	string temp;
	while(getline(inst, temp, ' ')) 
		tokens.push_back(temp);
	
    // Pack instruction based on format
	switch(format_of(tokens[0])) {
		case R: 
            // cout << "instruction " << tokens[0] << " is r type" << endl;
            return make_r_type(tokens); 
		case I: 
            // cout << "instruction" << tokens[0] << " is i type" << endl;
            return make_i_type(tokens);
		case J: 
            // cout << "instruction" << tokens[0] << " is j type" << endl;
            return make_j_type(tokens);
	}
    cout << "opcode of unrecognized format: " << tokens[0] << endl;
    exit(-1);
}

// parses an input file line by line and packs the corresponding instruction.
void assemble(string file) {
	ifstream in;
	
	// Check if target is valid
    //in.open("./in/" + file);
    in.open(file);
	if (!in.is_open()) {
		cout << "unable to open file ./in/" << file << endl;
		exit(-1);
	}

	ofstream out;
    // TODO: clear /out/ of any matching file a la make clean to ensure files are always freshly generated
	out.open("./out/" + file.substr(0, file.length() - 1 - 3) +".r3k");

	// Start assembling line by line
	string line;
	while(getline(in, line, '\n')) {
		out << build_instruction(line) << endl;
	}

	// Close everything up
	in.close();
	out.close();
}

int main(int argc, char** argv) {
    if(argc == 1) {
        cout << "Specify .ily file(s) in ./in/ to assemble" << endl;
        exit(0);
    }

    if(*(argv[1]) == '*') { // Assemble every file in ./in/
        // TODO: this is just gonna be iterating over every directory entry instead of argv
    }
    else { // Assemble just what they specify
        for(int i = 1; argv[i] != NULL; i++)
            assemble(argv[i]);
    }

    return 0;
}
