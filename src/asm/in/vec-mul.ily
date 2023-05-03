li r0 0
li r1 4
li r2 0
.loopstart lw r4 r0 20
lw r5 r0 24 
mul r6 r5 r4
add r2 r2 r6
addi r0 r0 1
bne r0 r1 .loopstart
sw r2 r1 40
hcf
