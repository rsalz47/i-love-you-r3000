// words and lines values taken from slide deck 7 example of memory
// calculations.
#define WORDS_PER_LINE 4
#define NUM_LINES 32

struct mem_access {
    int sucess;
    uint32_t data;
    uint32_t addr;
    int delay_timer;
};

class Memory {
   public:
    // spent an hour debugging this. using memory[524288][4] is too large for
    // the code stack. using defaults from slides
    uint32_t memory[NUM_LINES][WORDS_PER_LINE];

    // return value stored memory
    int fetch(mem_access *fetch_req) {
        if (fetch_req->delay_timer != 0) {
            fetch_req->delay_timer -= 1;
            return -1;
        }
        // after waiting the appropriate amount of time,
        // fetch from the memory array at ADDR
        fetch_req->data = this->memory[(fetch_req->addr / WORDS_PER_LINE) %
                                       (WORDS_PER_LINE * NUM_LINES)]
                                      [fetch_req->addr % WORDS_PER_LINE];
        fetch_req->sucess = 1;
        return 1;
    }
    // stores data in memory[addr]
    int store(mem_access *store_req) {
        if (store_req->delay_timer != 0) {
            store_req->delay_timer -= 1;
            return -1;
        }
        // after waiting the appropriate amount of time,
        // store DATA in the memory array at ADDR
        this->memory[(store_req->addr / WORDS_PER_LINE) %
                     (WORDS_PER_LINE * NUM_LINES)]
                    [store_req->addr % WORDS_PER_LINE] = store_req->data;
        store_req->sucess = 1;
        return 1;
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