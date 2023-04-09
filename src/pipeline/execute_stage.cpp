// As the name suggests, the execute function executes a decoded instruction.
// Much like the decode stage before it, this will largely just be a switch statement.

typedef struct decoded_instruction {
    std::string operation;
    uint32_t operand_1; // src1
    uint32_t operand_2; // src2
    char destination; // dest
    char shamt; // shift amount
    uint32_t addr_or_imm;
    uint32_t target_addr;
} decoded_instruction;


class ExecuteStage {
    private:
        MemoryStage memory_stage;

    public:
        bool blocked = false;
        decoded_instruction decoded;

    ExecuteStage(MemoryStage &m_s) {
        memory_stage = m_s;
    }

    // In one clock tick, execute executes the instruction that decode has decoded.
    void tick() {
       // execute an instruction 
    }
};
