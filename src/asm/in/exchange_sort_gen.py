# This program generates the assembly file that sorts the data
# in the incresing order using exchange sort given a file containing
# the data

# The filename is specified by command line arguments

# argv[1]: file that contains the data, with type suffix .dat
import sys
import re

data_filename = sys.argv[1];
# remove .dat and append .ily
output_filename = data_filename.split(".", 1)[0] + ".ily"

data = []

data_file = open(data_filename, 'r')

for line in data_file:
    line = re.sub("\s+", " ", line)
    line.strip()
    data_line = line.split(" ")
    data.extend(data_line)
data_file.close()
print(data)

size = len(data) - data.count("")
starting_addr = 1 + 2*size + 16

if starting_addr % 4:
    starting_addr += (4 - (starting_addr % 4))

output_file = open(output_filename, 'w+')

output_file.write("li r0 0\n")

for num in data:
    if num != "":
        output_file.write("li r1 " + str(num) + "\n")
        output_file.write("sw r1 r0 " + str(starting_addr) + "\n")
        size += 1
        starting_addr += 1

output_file.write("li r2 0\n\
li r3 99\n\
li r7 100\n\
.outerloop beq r2 r3 .exitouter\n\
addi r4 r2 1\n\
.innerloop beq r4 r7 .exitinner\n\
")
output_file.write("lw r5 r4 " + str(starting_addr) + "\n")
output_file.write("lw r6 r2 " + str(starting_addr) + "\n")
output_file.write("blt r6 r5 .exitif\n")
output_file.write("sw r5 r2 " + str(starting_addr) + "\n")
output_file.write("sw r6 r4 " + str(starting_addr) + "\n")
output_file.write("\
.exitif addi r4 r4 1\n\
j .innerloop\n\
.exitinner addi r2 r2 1\n\
j .outerloop\n\
.exitouter hcf")        
output_file.close()
