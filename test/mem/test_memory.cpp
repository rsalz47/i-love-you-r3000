#include <iostream>
#include "../../src/mem/memory.h"

#define IS_TRUE(x) { if (!(x))  std::cout <<__FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

// address is big
// correct clock cycle count
// 

//Test for fetch with 0 delay
void test_fetch_zero_delay() {    
  Memory mem; //delay 0
  uint32_t expected_data = 6;
  
  mem.memory[3][2] = expected_data;
  uint32_t* data = mem.fetch(3*NUM_LINES+2, 0);
  IS_TRUE(*data == expected_data);
}    


//Test for store with 0 delay
void test_store_zero_delay() {
  Memory mem;
  uint32_t address = 3*NUM_LINES+2;
  uint32_t data_stored = 222;
  
  uint32_t* data = mem.store(address, data_stored, 0);
  IS_TRUE(*data == data_stored);
}

//Test for fetch with nonzero delay
void test_fetch_nonzero_delay() {
  int delay = 5;
  uint32_t expected_data = 1024;
  uint32_t* data;

  Memory mem;
  mem.memory[3][2] = expected_data;
  int clock = 0;
  
  for(;;clock++) {
    data = mem.fetch(3*NUM_LINES+2,0);
    if (data != nullptr) {
      break;
    }
  }
  IS_TRUE(clock == delay);
  IS_TRUE(*data == expected_data);
  std::cout << *data << std::endl;
}


//Test for store with nonzero delay
void test_store_nonzero_delay() {
  int delay = 5;
  uint32_t data_stored = 1024;
  uint32_t* data;

  
  Memory mem;
  int clock = 0;
  
  for (;;clock++) {
    data = mem.store(3*NUM_LINES+2 ,data_stored, 0);
    if (data != nullptr) {
      break;
    }
  }

  IS_TRUE(clock == delay);
  IS_TRUE(*data == data_stored);  
}

//Test for load and fetch with large addresses
void test_memory_with_large_addresses() {
  

}



int main() {
  //  test_fetch();
  //  test_load();
  test_fetch_nonzero_delay();
  test_store_nonzero_delay();
}
