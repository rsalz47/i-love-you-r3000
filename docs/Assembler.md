# Overview
Our assembler implements the MIPS-1 ISA at an assembly and instruction level. 
While we do not capture the entirety of the MIPS-1 ISA-- notable omissions being
instructions pertinent to unsigned operations and coprocessor interaction-- a 
majority of the instruction set is implemented and follows defined convention.

The emitted assembly follows standard MIPS instruction encoding with no meaningful
deviations in functionality. The `funct` field of R-format instructions is currently
unused due to a lack of necessity; all implemented instructions can be described with the
6-bit opcode field. An exhaustive list of all implemented instructions is not currently 
available within this file, and is instead found in [assembler.h](../src/asm/assembler.h).
Because all instructions are stored within a std::map, the corresponding opcodes are self-
documenting.

## Usage
