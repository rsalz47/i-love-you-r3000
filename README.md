# I Love You R3000: A C++ Based MIPS R3000 Simulator
Start Date: March, 2023

This project is a software simulator of the MIPS R3000 processor.

# References
- [MIPS instruction encoding](https://www.dcc.fc.up.pt/~ricroc/aulas/1920/ac/apontamentos/P04_encoding_mips_instructions.pdf), via University of Porto
- [An overview of the opcodes available in the MIPS instruction set](https://mathcs.holycross.edu/~csci226/MIPS/summaryHO.pdf), via University of the Holy Cross
- [Register Field Breakdown](https://cgi.cse.unsw.edu.au/~cs3231/doc/mips.php#instructions), via UNSW Sydney
- [R3000 Software Reference Manual](https://usermanual.wiki/Document/r3000manual.723589236/view)
- Support from viewers like you.



#Tradeoffs considered
  1. Assembler is more complex while our assembly code itself becomes less complex
  2. Splitting L1 cache into code + data is justified by realizing that math benchmarks will use the same instructions but different math data per instruction
  3. 
