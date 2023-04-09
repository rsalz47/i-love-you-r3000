class WritebackStage {
private:
	uint32_t* pc;
	uint32_t* registers;
	//pending registers?

public:
    bool noop;
    bool branch;
    bool writeback;
    char reg;
    uint_32t value;

	void tick() {
		if (noop) {
            return;
		}
        
        // if instruction has branch, update PC
		//TODO: if JSR, update PC and return reg
		if (branch) {
			*pc = value;
            return;
		}

        if (!writeback) {
            // deal with dependencies
            return;
        }

        // the instruction needs to writeback
        // write to register
        registers[reg] = value;
        // deal with dependencies

	}
};
