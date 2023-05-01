li r0 0
li r5 1
li r1 1
li r2 1
li r3 15
li r6 40
.loopstart add r0 r5 r0
add r4 r1 r2
addi r1 r2 0
addi r2 r4 0
addi r6 r6 1
sw r4 r6 0
li r7 0
li r7 0
li r7 0
li r7 0
li r7 0
li r7 0
bne r0 r3 .loopstart
li r7 100
hcf