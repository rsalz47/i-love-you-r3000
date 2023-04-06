#include <iostream>
#include "../../src/mem/cache.cpp"

#define IS_TRUE(x) { if (!(x))  std::cout <<__FUNCTION__ << " failed on line " << __LINE__ << std::endl; }


// compute address according to the line number and the offset
uint32_t compute_addr(int line_num, int offset) {
	return line_num * 4 + offset;
}

// Test for cache's initial state
// all the valid bits should be set to 0
void test_cache_initial() {
	Memory mem;
	Cache cache(&mem);

	// check valid bits are all 0
	for (int i = 0; i < 16; i++) {
		IS_TRUE(cache.cache[i][7] == 0);
	}	
}    

// write data to all the addresses to fill the memory
// due to the write through policy, cache will not hold any data
// thus all valid bits are zero
void test_store_delay_zero() {
	Memory mem = Memory(0);
	Cache cache(&mem, 0);

	for (int i = 0; i < NUM_LINES; i++) {
		for (int j = 0; j < WORDS_PER_LINE; j++) {
			uint32_t addr = compute_addr(i, j);
			cache.store(addr, 777, 0);
		}
	}
	
	for (int i = 0; i < 16; i++) {
		IS_TRUE(cache.cache[i][7] == 0);
	}
}

// write data to fill the memory, then load from all the addresses
// cache should be filled and tag bits and valid bits are all ones
void test_load_delay_zero() {
	Memory mem = Memory(0);
	Cache cache(&mem, 0);
	uint32_t data = 777;

	// write data
	for (int i = 0; i < NUM_LINES; i++) {
		for (int j = 0; j < WORDS_PER_LINE; j++) {
			uint32_t addr = compute_addr(i, j);
			cache.store(addr, data, 0);
		}
	}

	// load data	
	for (int i = 0; i < NUM_LINES; i++) {
		for (int j = 0; j < WORDS_PER_LINE; j++) {
			uint32_t addr = compute_addr(i, j);	
			uint32_t* data_obtained = cache.load(addr, 0);

			uint32_t tag = (uint32_t)((unsigned char)addr >> 6) & 0b1111;
			uint32_t index = (uint32_t)((unsigned char)addr >> 2) & 0b1111;
			//check data loaded are correct
			IS_TRUE(*data_obtained == data);
			for (int k = 0; k < 4; k++) {
				IS_TRUE(cache.cache[index][2+k] == data);
			}
			//check valid bit
			IS_TRUE(cache.cache[index][7] == 1);
			//check tag bit
			IS_TRUE(cache.cache[index][0] == tag);
		}
	}
}

// test eviction

// test timing

int main() {
	test_cache_initial();
	test_store_delay_zero();
	test_load_delay_zero();
	std::cout << "test passed if there is no other output\n";
}
