// words and lines values taken from slide deck 7 example of memory calculations.
#define WORDS_PER_LINE 4
#define NUM_LINES 32
class Memory
{
public:
    // spent an hour debugging this. using memory[524288][4] is too large for the code stack. using defaults from slides
    uint32_t memory[NUM_LINES][WORDS_PER_LINE];

    // return value stored memory
    uint32_t fetch(uint32_t addr, int *delay_int)
    {
        // with this solution, any pipeline that calls fetch, will be waiting for fetch to return and does not need to call fetch every single time as a spin lock
        while (*delay_int != 0)
        {
            (*delay_int) = (*delay_int) - 1;
        }
        // after waiting the appropriate amount of time,
        // fetch from the memory array at ADDR
        uint32_t ret_val = this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)][addr % WORDS_PER_LINE];
        return ret_val;
    }
    // stores data in memory[addr]
    uint32_t store(uint32_t addr, uint32_t data, int *delay_int)
    {
        while (*delay_int != 0)
        {
            (*delay_int) = (*delay_int) - 1;
        }
        // after waiting the appropriate amount of time,
        // store DATA in the memory array at ADDR
        this->memory[(addr / WORDS_PER_LINE) % (WORDS_PER_LINE * NUM_LINES)][addr % WORDS_PER_LINE] = data;
        return 1;
    }
    // assign all memory locations to NULL (essentially 0s) 
    void reset()
    {
        for (int i = 0; i < NUM_LINES; i++)
        {
            for (int j = 0; j < WORDS_PER_LINE; j++)
            {
                // uint32_t(NULL) = 0 as it writes is as 32bits of 0 I think
                this->memory[i][j] = uint32_t(NULL);
            }
        }
    }
    // prints out a formatted memory status in the terminal 
    void cur_status()
    {
        {
            for (int i = 0; i < NUM_LINES; i++)
            {
                for (int j = 0; j < WORDS_PER_LINE; j++)
                {
                    printf("%15d | ",this->memory[i][j]);
                }
                printf("\n--------------- | --------------- | --------------- | --------------- | \n");
                
            }
        }
    }
};