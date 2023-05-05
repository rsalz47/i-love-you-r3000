li r0 0
li r1 45
sw r1 r0 100
li r1 85
sw r1 r0 101
li r1 93
sw r1 r0 102
li r1 2
sw r1 r0 103
li r1 30
sw r1 r0 104
li r1 99
sw r1 r0 105
li r1 50
sw r1 r0 106
li r1 64
sw r1 r0 107
li r1 8
sw r1 r0 108
li r1 23
sw r1 r0 109
li r2 0
li r3 9
li r7 10
.outerloop beq r2 r3 .exitouter
addi r4 r2 1
.innerloop beq r4 r7 .exitinner
lw r5 r4 100
lw r6 r2 100
blt r6 r5 .exitif
sw r5 r2 100
sw r6 r4 100
.exitif addi r4 r4 1
j .innerloop
.exitinner addi r2 r2 1
j .outerloop
.exitouter hcf