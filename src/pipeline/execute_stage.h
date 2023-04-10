#ifndef EXECUTE_STAGE_H
#define EXECUTE_STAGE_H

// As the name suggests, the execute function executes a decoded instruction.
// Much like the decode stage before it, this will largely just be a switch statement.

#include "memory_stage.h"

// input
typedef struct decoded_instruction {
    // R-format: opcode + destination + value_1 + value_2 + shamt
    // I-format: opcode + destination + value_1 + imm
    //       lw: opcode + stored_value + value_1 + imm
    // J-format: opcode + target_addr
    std::string operation;
    char opcode; // opcode of the instruction
    uint32_t operand_1; // src1
    uint32_t operand_2; // src2
    char destination; // dest
    char shamt; // shift amount
    uint32_t addr_or_imm;
    uint32_t target_addr;

    uint32_t dest_value;
} decoded_instruction;

class ExecuteStage {
 private:
    MemoryStage &memory_stage;

 public:
    bool noop = true;
    bool blocked = false;
    decoded_instruction decoded;
    executed_instruction executed;

    ExecuteStage(MemoryStage &m_s);

    // In one clock tick, execute executes the instruction that decode has decoded.
    void tick();
};
#endif /* EXECUTE_STAGE_H */
