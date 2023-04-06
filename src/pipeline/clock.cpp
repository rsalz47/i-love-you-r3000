#include "writebackstage.cpp"

class Clock {
    int cycle_count;
    WriteBackStage* wb_stage;

    Clock(WriteBackStage* wb_stage) {
        cycle_count = 0;
        this->wb_stage = wb_stage;
    }        
    
    void tick() {
        cycle_count++;
        wb_stage.writeback();
    }
};
