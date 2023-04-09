class MemoryStage {
    WritebackStage* wb_stage;
    ExecuteStage* ex_stage;

    Cache* cache;

    //instruction info
    bool noop;
    // can use several flags, or just store the opcode and parse the opcode in mem()?
    bool mem; // mem access or not
    bool store; // store or load
    int reg;
    uint32_t addr;
    uint32_t value;

    void mem() {
        if (noop) {
            ex_stage->ex(0);
        }
        if (!mem) {
            // if not mem, pass the instruction (reg + value) to wb
            wb_stage->reg = reg;
            wb_stage->value = value;
            ex_stage->ex(0);
        }        
        if (store) {
            uint32_t* data = cache->store(addr, value, 4); // memory stage id = 4
            if (data == nullptr) {
                wb_stage->noop = true;
                ex_stage->ex(1); // call E with blocked
            } else {
                // for a store, writeback does not need to do anything?
                wb_stage->noop = true;
                ex_stage(0);
            }
        } else { // load
            uint32_t* result = cache->load(addr, cache->store(addr, 4));
            if (result == nullptr) {
                wb_stage->noop = true;
                ex_stage(1);
            } else {
                wb_stage->noop = false;
                wb_stage->reg = reg;
                wb_stage->value = *result;                    
                ex_stage(0);
            }                                               
        }
    }
        
};
