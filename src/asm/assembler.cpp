#include <sstream>
#include <iostream>
#include <fstream> 
#include <vector>

#include "assembler.h"

using namespace std;

unsigned long make_r_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = RFormat::RTypes[op];

    if(op == "add") {
        return opc; 
    }
    else if(op == "sub") {
        return opc; 
    }
    else if(op == "mul") {
        return opc; 
    }
    else if(op == "div") {
        return opc; 
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
        return opc; 
    }
    else if(op == "or") {
        return opc; 
    }
    else if(op == "xor") {
        return opc; 
    }
    else if(op == "nor") {
        return opc; 
    }
    else if(op == "jr") {
        return opc; 
    }
    else if(op == "jral") {
        return opc; 
    }
    else if(op == "move") {
        return opc; 
    }
    else if(op == "seq") {
        return opc; 
    }
    else if(op == "sge") {
        return opc; 
    }
    else if(op == "sgt") {
        return opc; 
    }
    else if(op == "sle") {
        return opc; 
    }
    else if(op == "slt") {
        return opc; 
    }
    else if(op == "sne") {
        return opc; 
    }
    return instruction;
}

unsigned long make_i_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = IFormat::ITypes[op];

    if(op == "addi") {
        return opc; 
    }
    else if(op == "subi") {
        return opc; 
    }
    else if(op == "muli") {
        return opc; 
    }
    else if(op == "divi") {
        return opc; 
    }
    else if(op == "slti") {
        return opc; 
    }
    else if(op == "andi") {
        return opc; 
    }
    else if(op == "ori") {
        return opc; 
    }
    else if(op == "xori") {
        return opc; 
    }
    else if(op == "sw") {
        return opc; 
    }
    else if(op == "lw") {
        return opc; 
    }
    else if(op == "li") {
        return opc; 
    }
    else if(op == "b") {
        return opc; 
    }
    else if(op == "beq") {
        return opc; 
    }
    else if(op == "bne") {
        return opc; 
    }
    else if(op == "bgt") {
        return opc; 
    }
    else if(op == "blt") {
        return opc; 
    }
    else if(op == "bgtz") {
        return opc; 
    }
    else if(op == "bltz") {
        return opc; 
    }
    else if(op == "bgte") {
        return opc; 
    }
    else if(op == "blte") {
        return opc; 
    }
    else if(op == "bgtez") {
        return opc; 
    }
    else if(op == "bltez") {
        return opc; 
    }
    return instruction;
}

unsigned long make_j_type(vector<string> tokens) {
    unsigned long instruction = 0x00000000;
    string op = tokens[0];
    unsigned long opc = JFormat::JTypes[op];

    if(op == "j") {
        return opc; 
    }
    else if(op == "jal") {
        return opc; 
    }
    else if(op == "nop") {
        return opc; 
    }
    else if(op == "hcf") {
        return opc; 
    }
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
	in.open("./in/" + file);
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
