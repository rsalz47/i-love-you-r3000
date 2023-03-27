// words and lines values taken from slide deck 7 example of memory
// calculations.
#include "memory.h"
// remove mem_access
// add delay_int and in_use to memory class
// rework functions to work with above changes

class Memory {
   public:
    int delay_timer = DEFAULT_DELAY;
    // will be polled by function calling load or store
    bool in_use = false;
    // pipeline*
    int cur_caller_id = -1;  // this is to return to the correct person to be
                             // replaced with pipeline stage

    // spent an hour debugging this. using memory[524288][4] is too large for
    // the code stack. using defaults from slides
    uint32_t memory[NUM_LINES][WORDS_PER_LINE];

    // This returns a pointer to the start of the matching line of the addr. For
    // example, for addr 9, with line length 4, it will return memory[2][0] as
    // the address.

    // to access the rest of the words, you simply add the word offset to the
    // returned address for example,
    //    cout << *(main_mem.fetch_cache_ver(addr 9)<this will return
    //    memory[2][0] / addr 8> + 1<adding 1 to addr 8 will give addr 9 >) <<
    //    endl;
    uint32_t* fetch_cache_ver(uint32_t addr,int whois_calling) {
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
        this->delay_timer = DEFAULT_DELAY;
        this->in_use = false;
        cur_caller_id = -1;  // reset caller id
        return &(this->memory[(addr / WORDS_PER_LINE)][0]);
    }
    uint32_t* store_cache_ver(uint32_t addr, uint32_t data) {
        // assigning data to address
        this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
                    [addr % WORDS_PER_LINE] = data;
        return &(
            this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
                        [addr % WORDS_PER_LINE]);
    }
    uint32_t* fetch(uint32_t addr, int whois_calling) {
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
        this->delay_timer = DEFAULT_DELAY;
        this->in_use = false;
        cur_caller_id = -1;  // reset caller id
        return &(
            this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
                        [addr % WORDS_PER_LINE]);
    }
    uint32_t* store(uint32_t addr, uint32_t data, int whois_calling) {
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
        this->delay_timer = DEFAULT_DELAY;
        this->in_use = false;
        cur_caller_id = -1;

        // assigning data to address
        this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
                    [addr % WORDS_PER_LINE] = data;

        return &(
            this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)]
                        [addr % WORDS_PER_LINE]);
    }

    // assign all memory locations to NULL (essentially 0s)
    void reset() {
        for (int i = 0; i < NUM_LINES; i++) {
            for (int j = 0; j < WORDS_PER_LINE; j++) {
                // uint32_t(NULL) = 0 as it writes is as 32bits of 0
                this->memory[i][j] = uint32_t(NULL);
            }
        }
    }

    // prints out a formatted memory status in the terminal
    void cur_status() {
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
};
