#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "cache.cpp"
    
void print_options(int clock_cycle, int dram_delay, int cache_delay) {
  // future: set associativity, enable/disable cache
  std::cout << "+--------------------------------------------------------+" << std::endl;
  std::cout << "| Welcome to I-Love-You-R3000!                           |" << std::endl;          
  printf("| Current clock cycle count: %-28d|\n", clock_cycle);
  printf("| Current DRAM delay: %-35d|\n", dram_delay);
  printf("| Current Cache delay: %-34d|\n", cache_delay);    
  std::cout << "| Select from the options below:                         |" << std::endl;          
  std::cout << "| 1. Load a file containing load and store instructions  |" << std::endl;
  std::cout << "| 2. Enter an instruction/command:                       |" << std::endl;
  std::cout << "|      - Load : L addr stage_num                         |" << std::endl;
  std::cout << "|      - Store: S addr value stage_num                   |" << std::endl;
  std::cout << "|      - Read:  R addr stage_num                         |" << std::endl;
  std::cout << "|      - Write: W addr value stage_num                   |" << std::endl;
  std::cout << "|      - View:  V cache/dram line                        |" << std::endl;	
  std::cout << "| 3. Display DRAM                                        |" << std::endl;
  std::cout << "| 4. Display Cache                                       |" << std::endl;
  std::cout << "| 5. Reset Cache                                         |" << std::endl;
  std::cout << "| 6. Reset clock cycle count                             |" << std::endl;
  std::cout << "| 7. Set DRAM delay                                      |" << std::endl;
  std::cout << "| 8. Set Cache delay                                     |" << std::endl;
  std::cout << "| 0. Quit the program                                    |" << std::endl;
  std::cout << "+--------------------------------------------------------+" << std::endl;
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

void view_cache(Cache& cache, uint32_t addr) {
  uint32_t index = (uint32_t)((unsigned char)addr >> 2) & 0b1111;
  for (int i = 0; i < 8 ; i++) {					
    printf("%15d |", cache.cache[index][i]);
  }
  std::cout << std::endl;
}

void view_dram(Cache& cache, uint32_t addr) {
  for (int i = 0; i < WORDS_PER_LINE; i++) {
    printf("%15d |", cache.main_mem->memory[addr/4][i]);
  }
  std::cout << std::endl;
}

void print_memory_info(Cache& cache, uint32_t addr) {	
  std::cout << std::string(136, '-') << std::endl; 
  std::cout << "dram info:\n";
  view_dram(cache, addr);
  std::cout << "cache info:\n";
  view_cache(cache, addr);
  std::cout << std::string(136, '-') << std::endl;
}


// there are view possible type of instructions/commands:
// load:  L addr  stage
// single read: R addr stage
// store: S value addr stage
// singel write: W addr data statge
// TODO view command: V level line, where level is cache or mem
void run_instruction(Cache& cache, volatile int& clock, std::string const &instruction) {
  std::vector<std::string> out;
  std::string old_instr = instruction;
  tokenize(instruction, " ", out);
  if (out.size() == 3) {
    // load instruction or a single read command or view command		
    if (out[0] != "l" && out[0] != "L" && out[0] != "r" && out[0] != "R" && out[0] != "V") {
      // error
      std::cout << "wrong command" << std::endl;
      return;
    }
    // handle the view command
    if (out[0] == "V" || out[0] == "v") {
      int line_num = static_cast<int>(std::stoul(out[2]));
      if (out[1] == "dram") {
        view_dram(cache, line_num);
      } else if (out[1] == "cache") {
        view_cache(cache, line_num);
      } else {
        std::cout << "invalid command" << std::endl;
      }
      return;
    }		   					
    uint32_t addr = static_cast<uint32_t>(std::stoul(out[1]));
    uint32_t stage_id = static_cast<int>(std::stoul(out[2]));
    uint32_t* result;
    if (out[0] == "l" || out[0] == "L") {
      // a load instruction, run till the load succeeds
      while (true) {
        result = cache.load(addr, stage_id);
        if (result != nullptr) {
          // load success
          printf("%-10s finishes at cycle %d\n", old_instr.c_str(), clock);
          print_memory_info(cache, addr);
          clock++;
          return;
        }
        clock++;
      }
    } else { 
      result = cache.load(addr, stage_id);
      if (result == nullptr) {
        std::cout << "wait\n";
      } else {
        std::cout << "read success!\n";
      }
      clock++;
      print_memory_info(cache, addr);
      return;
    }
  } else if (out.size() == 4) {
    // store instruction or a single write command
    if (out[0] != "s" && out[0] != "S" && out[0] != "w" && out[0] != "W") {
      std::cout << "wrong command" << std::endl;
      return;
    }
    uint32_t addr = static_cast<uint32_t>(std::stoul(out[1]));
    uint32_t data = static_cast<uint32_t>(std::stoul(out[2]));
    uint32_t stage_id = static_cast<int>(std::stoul(out[3]));
    uint32_t* result;
    if (out[0] == "s" || out[0] == "S") {
      // a store instruction, run till the store succeeds
      while (true) {
        result = cache.store(addr, data, stage_id);
        if (result != nullptr) {
          // store success
          printf("%-10s finishes at cycle %d\n", old_instr.c_str(), clock);
          print_memory_info(cache, addr);
          clock++;
          return;
        }
        clock++;
      }
    } else {
      cache.store(addr, data, stage_id);
      if (result == nullptr) {
        std::cout << "wait\n";
      } else {
        std::cout << "write success at cycle " << clock << std::endl;
      }						
      clock++;
      // print memory info
      print_memory_info(cache, addr);
      return;
    }		
  } else {
    std::cout << "The instruction/command entered does not have proper length.\n";
  }
}

void run_instructions(Cache& cache, volatile int& current_cycle, std::string filename) {
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    std::cout << "Cannot open file\n";
    return;
  }
  std::string line;
  while(std::getline(file, line)) {
    run_instruction(cache, current_cycle, line);
  }
  file.close();	
}  

int main() {
  volatile int clock = 0;
  int dram_delay = DEFAULT_DELAY;
  int cache_delay = CACHE_DELAY_DEFAULT;
  Memory main_mem;
  Cache cache = Cache(&main_mem, cache_delay);

  char option;
  while (true) {
    print_options(clock, dram_delay, cache_delay);
    std::cin >> option;
    switch(option){
    case '1':{
      std::string filename;
      std::cout << "Enter the file name: ";
      std::cin.ignore();
      std::cin >> filename;
      filename = "../../test/mem/" + filename;
      std::cout << filename << std::endl;
      run_instructions(cache, clock, filename);
      break;
    }
    case '2': {
      std::string instruction;
      std::cout << "Instruction or command: ";
      std::cin.ignore();
      std::getline(std::cin, instruction);
      run_instruction(cache, clock, instruction);
      break;
    }
    case '3': {
      cache.main_mem->cur_status();
      break;
    }
    case '4': {
      cache.cur_status();
      break;
    }
    case '5': {
      cache.reset();
      break;
    }
    case '6': {
      clock = 0;
      break;
    }
    case '7': {
      std::cout << "Enter new DRAM delay: ";
      std::cin >> dram_delay;
      cache.main_mem->initial_delay = dram_delay;
      cache.main_mem->delay_timer = dram_delay;
      break;
    }
    case '8': {
      std::cout << "Enter new Cache delay: ";
      std::cin >> cache_delay;
      cache.initial_delay = cache_delay;
      cache.cache_delay_timer = cache_delay;
      break;
    }
    case '0':
      return 0;
    }
  }
}  
