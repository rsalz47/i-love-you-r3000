#ifndef EXECUTE_STAGE_H
#define EXECUTE_STAGE_H

// As the name suggests, the execute function executes a decoded instruction.
// Much like the decode stage before it, this will largely just be a switch statement.

#include "memory_stage.h"

class ExecuteStage {
 private:
    MemoryStage memory_stage;

 public:
    bool blocked = false;
    decoded_instruction decoded;

    ExecuteStage(MemoryStage &m_s);

    // In one clock tick, execute executes the instruction that decode has decoded.
    void tick();
};
#endif /* EXECUTE_STAGE_H */
