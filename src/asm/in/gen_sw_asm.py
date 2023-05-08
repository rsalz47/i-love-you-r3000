# This program generates the assembly file that stores
# some specified data in a file to memory with specified # starting address
# argv[0]: starting address
# argv[1]: file that contains the data
import sys

starting_addr = int(sys.argv[1]);
data_filename = sys.argv[2];
# data filename has the format .dat
output_filename = data_filename.split(".", 1)[0] + ".ily"

data = []

data_file = open(data_filename, 'r')

for line in data_file:
    data_line = line.split(" ")
    data.extend(data_line)
data_file.close()

output_file = open(output_filename, 'w+')

output_file.write("li r0 0\n")

for num in data:
    output_file.write("li r1 " + str(num) + "\n")
    output_file.write("sw r1 r0 " + str(starting_addr) + "\n")
    starting_addr += 1
output_file.close()
    
    

    
