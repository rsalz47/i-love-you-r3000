li r0 10
li r1 0
li r2 0
li r3 0
li r4 0
li r5 700
li r6 800
li r16 0
.j-loop-body li r1 0
li r4 0    
.k-loop-body mul r7 r2 r0
add r7 r4 r7
add r7 r5 r7
lw r8 r7 0
mul r9 r4 r0
add r9 r3 r9
add r9 r6 r9
lw r10 r9 0
mul r10 r8 r10
add r1 r1 r10
addi r4 r4 1
bne r0 r4 .k-loop-body
mul r15 r2 r0
add r15 r3 r15
add r15 r16 r15
sw r1 r15 0
addi r3 r3 1
bne r0 r3 .j-loop-body
addi r2 r2 1
li r3 0    
bne r0 r2 .j-loop-body
hcf
