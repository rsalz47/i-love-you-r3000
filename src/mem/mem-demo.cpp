#include <iostream>

void print_options(int clock_cycle) {
  // future: set associativity, enable/disable cache, display clock cycle
  // display/set DRAM/cache delay
  std::cout << "+--------------------------------------------------------+" << std::endl;
  //  printf("%-56s |\n","| Welcome to I-Love-You-R3000!");          
  std::cout << "| Welcome to I-Love-You-R3000!                           |" << std::endl;
  std::cout << "| Current clock cycle count: " << clock_cycle << "                           |" << std::endl;

  std::cout << "| Select from options below:                             |" << std::endl;
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
  std::cout << "| A. Reset clock cycle count                             |" << std::endl;
  std::cout << "| F. Quit the program                                    |" << std::endl;
  std::cout << "+--------------------------------------------------------+" << std::endl;
}

int main() {
  volatile int clock = 0;
  while (true) {
    print_options(255);
    return 1;
  }
}  
