class MemoryStage {
private:
    WritebackStage* wb_stage;
    Cache* cache;

    
public:
    bool blocked = false;
    decoded_instruction decoded;
    bool noop = true;

    MemoryStage(WritebackStage* wb_stage, Cache* cache) {
        this->wb_stage = wb_stage;
        this->cache = cache;
    }
    
    void tick() {
        if (noop) {
            return;
        }
        // if not mem and writeback, pass the instruction (reg + value) to wb
        if (decoded.operation != "sw" || decode.operation != "lw") {
            // add, sub, mul, div, li all require writeback
            wb_stage->writeback = true;
            wb_stage->reg = decoded.destination;
            wb_stage->value = decoded.target_addr;
            return;
        }

        if (decoded.operation == "sw") {
            //TODO need to modify the arguments in the future
            uint32_t* data = cache->store(addr, value, 4); // memory stage id = 4
            if (data == nullptr) {
                wb_stage->noop = true;
                blocked = true;
            } else {
                // for a store, writeback does not need to do anything?
                wb_stage->noop = true;
                wb_stage->writeback = false;
                blocked = false;
            }
        } else { // load
            //TODO need to modify the arguments in the future
            uint32_t* result = cache->load(addr, cache->store(addr, 4));
            if (result == nullptr) {
                wb_stage->noop = true;
                blocked = true;
            } else {
                wb_stage->noop = false;
                wb_stage->writeback = true;
                wb_stage->reg = reg;
                wb_stage->value = *result;                    
                blocked = false;
            }                                               
        }
    }
        
};
