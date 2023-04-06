class WritebackStage {
	MemStage* mem_stage;
	uint32_t* pc;

	uint32_t* registers;
	//pending registers?

	//instruction info
	bool noop; // whether the instruction is a noop
	bool branch; // whetehr the instruction is a branch
	int reg;
	uint32_t value;

	void writeback() {
		if (!noop) {
			// write to register
			registers[reg] = value;
		}

		// if instruction has branch, update PC
		//TODO: if JSR, update PC and return reg
		if (branch) {
			*pc = value;
		}

		// call mem stage
		mem_stage->mem();
	}
};
