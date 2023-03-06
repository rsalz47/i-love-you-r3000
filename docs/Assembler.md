# Overview
This assembler implements the MIPS-1 ISA at an assembly and instruction level. 
While it does not capture the *entirety* of the MIPS-1 ISA-- notable omissions being
instructions pertinent to unsigned operations and coprocessor interaction-- a 
majority of the instruction set is implemented and follows defined convention.

The emitted assembly follows standard MIPS instruction encoding with no meaningful
deviations in functionality. The `funct` field of R-format instructions is currently
unused due to a lack of necessity; all implemented instructions can be described with the
6-bit opcode field. An exhaustive list of all implemented instructions is not currently 
available within this file, and is instead found in [assembler.h](../src/asm/assembler.h).
Because all instructions are stored within a std::map, the corresponding opcodes are self-documenting.

## Usage
Within src/asm/, compile `assembler.cpp` with your favorite C++ compiler (g++ was used during development). Once compiled, pass in the names of anything in `asm/in/` that you would like assembled as a command line flag. For instace, to compile the provided samples `asm/in/foo.ily` and `asm/in/bar.ily`, the command would look like
`./assembler foo.ily bar.ily`. The assembled files will then be output in the `asm/out/` directory.
Note: If out folder does not exist, make one! (To be fixed)


