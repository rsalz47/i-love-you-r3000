#include <iostream>
#include <fstream> 
#include <vector>
#include <bitset>
#include <filesystem>
#include <sstream>

#include "assembler.h"
#include "../mem/registers.h"

using namespace std;
map<string, int> symbols;

unsigned long make_r_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = RFormat::RTypes[op];

    if(op == "add") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);

    }
    else if(op == "sub") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "mul") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "div") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
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
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "or") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "xor") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "nor") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
   else if(op == "jr") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
    }
    else if(op == "jral") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
    }
    else if(op == "move") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
    }
    else if(op == "seq") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sge") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sgt") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sle") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
   }
    else if(op == "slt") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    else if(op == "sne") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= RFormat::pack_rd(RegistersToBits[tokens[3]]);
        instruction |= RFormat::pack_shamt((unsigned long) 0x0);
        instruction |= RFormat::pack_funct((unsigned long) 0x0);
    }
    cout << bitset<32>(instruction) << endl;
    return instruction;
}

unsigned long make_i_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = IFormat::ITypes[op];

    if(op == "addi") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "subi") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "muli") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "divi") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "slti") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "andi") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "ori") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "xori") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "sw") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "lw") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "li") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= IFormat::pack_addr_imm(stoul(tokens[2]));
    }
    else if(op == "b") {
        instruction |= pack_opcode(opc);
        if(tokens[1][0] == '.') {
            cout << "Branch has parameter that is label " << tokens[1] << endl;
            cout << "Label " << tokens[1] << " corresponds to address " << symbols[tokens[1]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[1]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[1]));
    }
    else if(op == "beq") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchEQ has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[1] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bne") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchNE has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bgt") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchGT has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "blt") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchLT has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bgtz") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchGTZ has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bltz") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchLTZ has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
 
    }
    else if(op == "bgte") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchGTE has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "blte") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchLTE has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bgtez") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);
        if(tokens[3][0] == '.') {
            cout << "BranchGTEZ has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    else if(op == "bltez") {
        instruction |= pack_opcode(opc);
        instruction |= pack_rs(RegistersToBits[tokens[1]]);
        instruction |= pack_rt(RegistersToBits[tokens[2]]);

        if(tokens[3][0] == '.') {
            cout << "BranchLTEZ has parameter that is label " << tokens[3] << endl;
            cout << "Label " << tokens[3] << " corresponds to address " << symbols[tokens[3]] << endl;
            instruction |= IFormat::pack_addr_imm(symbols[tokens[3]]);
        }
        else
            instruction |= IFormat::pack_addr_imm(stoul(tokens[3]));
    }
    cout << bitset<32>(instruction) << endl;
    return instruction;
}

unsigned long make_j_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = JFormat::JTypes[op];

    if(op == "j") {
        instruction |= pack_opcode(opc);
        
        if(tokens[1][0] == '.') {
            cout << "Jump has parameter that is label " << tokens[1] << endl;
            cout << "Label " << tokens[1] << " corresponds to address " << symbols[tokens[1]] << endl;
            instruction |= JFormat::pack_target_addr(symbols[tokens[1]]);
        }
        else
            instruction |= JFormat::pack_target_addr(stoul(tokens[1]));

    }
    else if(op == "jal") {
        instruction |= pack_opcode(opc);
        if(tokens[1][0] == '.') {
            cout << "Jump And Link has parameter that is label " << tokens[1] << endl;
            cout << "Label " << tokens[1] << " corresponds to address " << symbols[tokens[1]] << endl;
            instruction |= JFormat::pack_target_addr(symbols[tokens[1]]);
        }
        else
            instruction |= JFormat::pack_target_addr(stoul(tokens[1]));
    }
    else if(op == "nop") {
        return opc << 26; 
    }
    else if(op == "hcf") {
        instruction |= pack_opcode(opc);
        instruction |= JFormat::pack_target_addr(0x0);
    }
    cout << bitset<32>(instruction) << endl;
    return instruction;
}

unsigned long build_instruction(string instr) {
	// Tokenize instruction
	vector<string> temp_tokens;
    vector<string> tokens;
	stringstream inst(instr);
	string temp;
	while(getline(inst, temp, ' ')) 
		temp_tokens.push_back(temp);
	
    if(temp_tokens[0][0] == '.') {
        cout << "encountered label " << temp_tokens[0] << endl;
        tokens.assign(temp_tokens.begin() + 1, temp_tokens.end());
    }
    else {
        tokens = temp_tokens;
    }

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

void build_symbol_table(string line, int line_num) {
    vector<string> tokens;
	stringstream instr(line);
	string temp;
	while(getline(instr, temp, ' ')) 
		tokens.push_back(temp);

    if(tokens[0][0] == '.')  {
        cout << "Encountered symbol " << tokens[0] << " at line " << line_num << endl;
        cout << "inserting " << tokens[0] << endl;
        symbols.insert({tokens[0], line_num});
    }
}

// parses an input file line by line and packs the corresponding instruction.
void assemble(string file) {
	ifstream in;
	
	// Check if target is valid
  in.open(file);
  
	if (!in.is_open()) {
		cout << "unable to open file ./in/" << file << endl;
		exit(-1);
	}

	ofstream out;
    string outfile = "./out/" + file.substr(0, file.length() - 1 - 3) +".r3k";

    // Delete any pre-existing assembled file matching the one we want to generate
    // and open up a new file 
    string temp = "rm " + outfile;
    system(temp.c_str());
    out.open(outfile);

	// Start assembling line by line 
	string line;

    int line_num = 0;
    cout << "Building symbol table..." << endl;
	while(getline(in, line)) {
        build_symbol_table(line, line_num);
        line_num++;
    }
    cout << "Symbol table built. " << endl;

    in.clear();
    in.seekg(0, ios::beg);
    
    cout << "Assembling instructions..." << endl;
    while(getline(in, line)) {
		out << build_instruction(line) << endl;
	}
    cout << "Assembly complete. Assembled machine code can be found in " << outfile << endl;

	// Close everything up
	in.close();
	out.close();
}
