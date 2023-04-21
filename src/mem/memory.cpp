// words and lines values taken from slide deck 7 example of memory
// calculations.
#include "memory.h"
// remove mem_access
// add delay_int and in_use to memory class
// rework functions to work with above changes

Memory::Memory(){}
	
Memory::Memory(int delay) {
    initial_delay = delay;
    delay_timer = delay;
}

void Memory::set_initial_delay(int delay) {
    initial_delay = delay;
    delay_timer = delay;
}

void Memory::reset_delay() {
    delay_timer = initial_delay;
}
	
uint32_t* Memory::fetch_cache_ver(uint32_t addr,int whois_calling) {
    if (this->in_use == false) {
        this->in_use = true;
        cur_caller_id = whois_calling;  // this ensures that each fetch is
        // unique to a single caller
    }
    if (!(this->in_use == true && whois_calling == cur_caller_id)) {
        return nullptr;  // says wait to other callers other than caller_id
    }
    if (this->in_use == true && whois_calling == cur_caller_id &&
        this->delay_timer > 0) {
        this->delay_timer -= 1;  // decrement for current caller
        return nullptr;
    }
    // delay reaches 0
    this->delay_timer = initial_delay;
    this->in_use = false;
    cur_caller_id = -1;  // reset caller id
    return &(this->memory[(addr / WORDS_PER_LINE)][0]);
}

uint32_t* Memory::store_cache_ver(uint32_t addr, uint32_t data) {
    // assigning data to address
    this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
        [addr % WORDS_PER_LINE] = data;
    return &(
             this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
             [addr % WORDS_PER_LINE]);
}

uint32_t* Memory::load(uint32_t addr, int whois_calling) {
    if (this->in_use == false) {
        this->in_use = true;
        cur_caller_id = whois_calling;  // this ensures that each fetch is
        // unique to a single caller
    }
    if (!(this->in_use == true && whois_calling == cur_caller_id)) {
        return nullptr;  // says wait to other callers other than caller_id
    }
    if (this->in_use == true && whois_calling == cur_caller_id &&
        this->delay_timer > 0) {
        this->delay_timer -= 1;  // decrement for current caller
        return nullptr;
    }
    // once you reach here in the code, delay_timer should be 0, so we reset
    // memory and free it for other calls
    this->delay_timer = initial_delay;
    this->in_use = false;
    cur_caller_id = -1;  // reset caller id
    return &(
             this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
             [addr % WORDS_PER_LINE]);
}

uint32_t* Memory::store(uint32_t addr, uint32_t data, int whois_calling) {
    if (this->in_use == false) {
        this->in_use = true;
        cur_caller_id = whois_calling;
    }
    if (!(this->in_use == true && whois_calling == cur_caller_id)) {
        return nullptr;
    }
    if (this->in_use == true && whois_calling == cur_caller_id &&
        this->delay_timer > 0) {
        this->delay_timer -= 1;
        return nullptr;
    }
    // once you reach reset memory as delay_timer = 0;
    this->delay_timer = initial_delay;
    this->in_use = false;
    cur_caller_id = -1;

    // assigning data to address
    this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
        [addr % WORDS_PER_LINE] = data;

    return &(
             this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
             [addr % WORDS_PER_LINE]);
}

void Memory::reset() {
    for (int i = 0; i < NUM_LINES; i++) {
        for (int j = 0; j < WORDS_PER_LINE; j++) {
            // uint32_t(NULL) = 0 as it writes is as 32bits of 0
            this->memory[i][j] = uint32_t(NULL);
        }
    }
}

void Memory::cur_status() {
    {
        for (int i = 0; i < NUM_LINES; i++) {
            for (int j = 0; j < WORDS_PER_LINE; j++) {
                printf("%15d | ", this->memory[i][j]);
            }
            printf(
                   "\n--------------- | --------------- | --------------- | "
                   "--------------- | \n");
        }
    }
}
