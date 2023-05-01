li r0 0
li r1 1
li r2 50
.loopstart add r0 r1 r0
bne r0 r2 .loopstart
li r4 100
hcf
