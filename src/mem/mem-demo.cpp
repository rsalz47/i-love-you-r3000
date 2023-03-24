#include <iostream>

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
  std::cout << "| 7. Display DRAM                                        |" <<
std::endl;
  std::cout << "| 8. Display Cache                                       |" << std::endl;
  std::cout << "| 9. Reset Cache                                         |" << std::endl;
  std::cout << "| A. Reset clock cycle count                             |"
<< std::endl;
  std::cout << "| B. Set DRAM delay                                      |" << std::endl;
  std::cout << "| C. Set Cache delay                                     |" << std::endl;
  std::cout << "| F. Quit the program                                    |" << std::endl;
  std::cout << "+--------------------------------------------------------+" << std::endl;
}

int main() {
  volatile int clock = 0;
  int dram_delay = 3;
  int cache_delay = 0;
  char option;
  while (true) {
    print_options(clock, dram_delay, cache_delay);
    std::cin >> option;
    switch(option){
      case '1':
	break;
      case '2':
	break;
      case '3':
	break;
      case '4':
	break;
      case '5':
	break;
      case '6':
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
