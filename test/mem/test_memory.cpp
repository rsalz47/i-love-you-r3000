#include <iostream>
#include "../../src/mem/memory.h"

#define IS_TRUE(x) { if (!(x))  std::cout <<__FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

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
    data = mem.fetch(3*WORDS_PER_LINE+2,0);
    if (data != nullptr) {
      break;
    }
  }
  IS_TRUE(clock == delay);
  IS_TRUE(*data == expected_data);
}


//Test for store with nonzero delay
void test_store_nonzero_delay() {
  int delay = 5;
  uint32_t data_stored = 1024;
  uint32_t* data;

  
  Memory mem;
  int clock = 0;
  
  for (;;clock++) {
    data = mem.store(3*WORDS_PER_LINE+2 ,data_stored, 0);
    if (data != nullptr) {
      break;
    }
  }

  IS_TRUE(clock == delay);
  IS_TRUE(*data == data_stored);  
}

//Test for load and fetch with large addresses
//The formula for memery access is
// memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)][addr % WORDS_PER_LINE])
//Want to test the case where (addr / WORDS_PER_LINE) is greater than NUM_LINES
void test_memory_with_large_addresses() {
  int delay = 5;
  uint32_t* data;
  uint32_t data_stored = 1024;
  
  Memory mem;
  int clock = 0;
  uint32_t addr = (NUM_LINES+1)*WORDS_PER_LINE;
  
  //store
  for (;;clock++) {
    data = mem.store(addr, data_stored, 0);
    if (data != nullptr) {
      break;
    }
  }

  IS_TRUE(clock == delay);
  IS_TRUE(*data == data_stored);

  //load
  clock = 0;
  for (;;clock++) {
    data = mem.fetch(addr, 0);
    if (data != nullptr) {
      break;
    }
  }
  IS_TRUE(clock == delay);
  IS_TRUE(*data == data_stored);
}



int main() {
  //  test_fetch_zero_delay();
  //  test_load_zero_delay();
  test_fetch_nonzero_delay();
  test_store_nonzero_delay();
  //  test_memory_with_large_addresses();
}
