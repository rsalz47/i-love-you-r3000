#include <iostream>
#include <string>

void print_options(int clock_cycle, int dram_delay, int cache_delay) {
	// future: set associativity, enable/disable cache
	std::cout << "+--------------------------------------------------------+" << std::endl;
	std::cout << "| Welcome to I-Love-You-R3000!                           |" << std::endl;          
	printf("| Current clock cycle count: %-28d|\n", clock_cycle);
	printf("| Current DRAM delay: %-35d|\n", dram_delay);
	printf("| Current Cache delay: %-34d|\n", cache_delay);    
	std::cout << "| Select from the options below:                         |" << std::endl;          
	std::cout << "| 1. Load a file containing load and store instructions  |" << std::endl;
	std::cout << "| 2. Enter a load instruction (L addr stage)             |" << std::endl;
	std::cout << "| 3. Enter a store instruction (S value addr stage)      |" << std::endl;
	std::cout << "| 4. Enter a read command (R addr stage)                 |" << std::endl;
	std::cout << "| 5. Enter a write command (W value addr stage)          |" << std::endl;
	std::cout << "| 6. Enter a view command (V level line)                 |" << std::endl;
	std::cout << "| 7. Display DRAM                                        |" << std::endl;
	std::cout << "| 8. Display Cache                                       |" << std::endl;
	std::cout << "| 9. Reset Cache                                         |" << std::endl;
	std::cout << "| A. Reset clock cycle count                             |" << std::endl;
	std::cout << "| B. Set DRAM delay                                      |" << std::endl;
	std::cout << "| C. Set Cache delay                                     |" << std::endl;
	std::cout << "| F. Quit the program                                    |" << std::endl;
	std::cout << "+--------------------------------------------------------+" << std::endl;
}

void run_instructions(Cache cache, int& current_cycle, std::string filename) {
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
		std::cout << "Cannot open file\n";
		return;
    }
    std::string line;
    while(std::getline(file, line)) {
		run_instruction(line);
	}  
	file.close();
} 

// there are view possible type of instructions/commands:
// load:  L addr  stage
// single read: R addr stage
// store: S value addr stage
// singel write: W addr data statge
// TODO view command: V level line, where level is cache or mem
void run_instruction(Cache cache, int& clock, std::string instruction) {
	std::vector<std::string> out;
	tokenize(line, " ", out); 
	if (out.size() == 3) {
		// load instruction or a single read command
		if (out[0] != "l" || out[0] != "L" || out[0] != 'r' || out[0] != 'R') {
			// error
			std::cout << "Supposed to be a load/read instruction/command, but not start with l/L or r/R\n";
			return;
		}            
		uint32_t addr = static_cast<uint32_t>(std::stoul(out[1]));
		uint32_t stage_id = static_cast<int>(std::stoul(out[2]));
		uint32_t* result;
		if (out[0] != "l" || out[0] != "L") {
			// a load instruction, run till the load succeeds
			while (true) {
				result = cache.fetch(addr, stage_id);
				if (result != nullptr) {
					// load success
					std::cout << line << " finishes at " << clock << std::endl;
					break;
				}
				clock++;
			}
		} else { 
			cache.fetch(addr, stage_id);
			clock++;
		}
	} else if (out.size() == 4) {
		// store instruction or a single write command
		if (out[0] != "s" || out[0] != "S" || out[0] != 'w' || out[0] != 'W') {
			std::cout << "Supposed to be a store/write instruction/command, but not start with s/S or w/W\n";
			return;
		}
		uint32_t addr = static_cast<uint32_t>(std::stoul(out[1]));
		uint32_t data = static_cast<uint32_t>(std::stoul(out[2]));
		uint32_t stage_id = static_cast<int>(std::stoul(out[3]));
		uint32_t* result;
		if (out[0] != "s" || out[0] != "S") {
			// a store instruction, run till the store succeeds
			while (true) {
				result = cache.store(addr, data, stage_id);
				if (result != nullptr) {
					// store success
					std::cout << line << " finishes at " << clock << std::endl;
					break;
				}
				clock++;
			}
		} else {
			cache.store(addr, data, stage_id);
			clock++;
		}		
	} else {
		std::cout << "The instruction/command entered does not have proper length.\n";
	}
}

// helper function to tokenize an instruction
void tokenize(std::string const &str, const char* delim, 
              std::vector<std::string> &out) { 
	char *token = strtok(const_cast<char*>(str.c_str()), delim); 
	while (token != nullptr) { 
		out.push_back(std::string(token)); 
		token = strtok(nullptr, delim); 
	} 
} 

int main() {
	Memory* main_mem;
	Cache* cache;
	volatile int clock = 0;
	int dram_delay = 3;
	int cache_delay = 0;
	char option;
	while (true) {
		print_options(clock, dram_delay, cache_delay);
		std::cin >> option;
		switch(option){
		case '1':
			std::string filename;
			std::cout << "Enter the file name: ";
			std::cin >> filename;
			run_instructions(cache, clock, filename);
			break;
		case '2':
		case '3':
		case '4':
		case '5':
			std::string instruction;
			std::cout << "Instruction or command: ";
			std::cin >> instruction;
			run_instruction(cache, clock, instruction);				
			break;
		case '6':
			// TODO
			break;
		case '7':
			break;
		case '8':
			break;
		case '9':
			break;
		case 'A':
		case 'a':
			clock = 0;
			break;
		case 'B':
		case 'b':
			std::cout << "Enter new DRAM delay: ";
			std::cin >> dram_delay;
			break;
		case 'C':
		case 'c':
			std::cout << "Enter new Cache delay: ";
			std::cin >> cache_delay;
			break;
		case 'F':
		case 'f':
			return 0;
		}
	}
}  
