#include <string>
#include <sstream>
#include <iostream>
#include <fstream> 
#include <vector>

using namespace std;

// I am fairly confident there is no better way to do this.
// Put in .h maybe? This is kind of a silly function anyway
int format_of(string opcode) {
	if(opcode == "AND"  ||
	   opcode == "OR"   ||
	   opcode == "XOR"  ||
	   opcode == "NOR"  ||
	   opcode == "ADD"  ||
	   opcode == "SUB"  ||
	   opcode == "MULT" ||
	   opcode == "DIV"  ||
	   opcode == "SLLV" ||
	   opcode == "SRLV" ||
	   opcode == "SRAV" ||
	   opcode == "JR"   ||
	   opcode == "JRAL" ||
	   opcode == "MOVE" ||
	   opcode == "SEQ"  ||
	   opcode == "SGE"  ||
	   opcode == "SGT"  ||
	   opcode == "SLE"  ||
	   opcode == "SLT"  ||
	   opcode == "SNE"
	   )
		return R;

	if(opcode == "SLTI" ||
	   opcode == "ANDI" ||
	   opcode == "ORI"  ||
	   opcode == "XORI" ||
	   opcode == "ADDI" ||
	   opcode == "SUBI" ||
	   opcode == "MULI" ||
	   opcode == "DIVI" ||
	   opcode == "SW"   ||
	   opcode == "LW"   ||
	   opcode == "LI"   ||
	   opcode == "BEQ"  ||
	   opcode == "BNE"  ||
	   opcode == "BGTZ" ||
	   opcode == "BLTZ" ||
	   opcode == "BGEZ" ||
	   opcode == "BLEZ" ||
	   opcode == "BGT"  ||
	   opcode == "BEGZ" ||
	   opcode == "BNEZ" ||
	   opcode == "BGE"  ||
	   opcode == "BLT"  ||
	   opcode == "BLE"  ||
	   opcode == "B"
	  )
		return I;

	if(opcode == "J"    ||
	   opcode == "JAL"  ||
	   opcode == "NOP"  ||
	   opcode == "HCF")
		return J;

    return -1;
}

unsigned long build_instruction(string instr, ofstream &out) {
	vector<string> tokens;
	stringstream inst(instr);
	string temp;

	// Tokenize instruction
	while(getline(inst, temp, ' ')) 
		tokens.push_back(temp);
	
    // Pack instruction based on format
	switch(format_of(tokens[0])) {
		case R: 
            return 0; 
		case I: 
            return 1;
		case J: 
            return 2;
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
		out << build_instruction(line, out) << endl;
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
