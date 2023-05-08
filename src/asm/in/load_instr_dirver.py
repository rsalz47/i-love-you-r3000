# This program generates code that loads the instructins into memory used
# in the driver code in pipeline/driver.cpp

import sys

instr_filename = sys.argv[1];

output_filename = instr_filename.split(".",1)[0] + ".driver";

instr_file = open(instr_filename, 'r')
output_file = open(output_filename, 'w+')

offset = 0
line_num = 0

for line in instr_file:
    output_file.write("memory.memory[" + str(line_num) + "][" + str(offset) + "] = " + line.strip() + ";\n");
    offset +=1    
    if offset % 4 == 0:
        offset = 0
        line_num += 1
instr_file.close()
output_file.close()       
