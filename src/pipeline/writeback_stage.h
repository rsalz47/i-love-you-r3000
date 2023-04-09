#ifndef WRITEBACK_STAGE_H
#define WRITEBACK_STAGE_H

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

class WritebackStage {
 private:
	uint32_t* pc;
	uint32_t* registers;
	//pending registers?

 public:
    bool noop;
    bool branch;
    bool writeback = false;
    char reg;
    uint32_t value;

	void tick();
};
#endif /* WRITEBACK_STAGE_H */
