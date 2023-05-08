li r0 0
li r1 1
sw r1 r0 96
li r1 2
sw r1 r0 97
li r1 3
sw r1 r0 98
li r1 4
sw r1 r0 99
li r1 5
sw r1 r0 100
li r1 6
sw r1 r0 101
li r1 7
sw r1 r0 102
li r1 8
sw r1 r0 103
li r1 1
sw r1 r0 104
li r1 2
sw r1 r0 105
li r1 3
sw r1 r0 106
li r1 4
sw r1 r0 107
li r1 5
sw r1 r0 108
li r1 6
sw r1 r0 109
li r1 7
sw r1 r0 110
li r1 8
sw r1 r0 111
li r1 5
sw r1 r0 112
li r1 6
sw r1 r0 113
li r1 7
sw r1 r0 114
li r1 8
sw r1 r0 115
li r1 1
sw r1 r0 116
li r1 2
sw r1 r0 117
li r1 3
sw r1 r0 118
li r1 4
sw r1 r0 119
li r1 5
sw r1 r0 120
li r1 6
sw r1 r0 121
li r1 7
sw r1 r0 122
li r1 8
sw r1 r0 123
li r1 1
sw r1 r0 124
li r1 2
sw r1 r0 125
li r1 3
sw r1 r0 126
li r1 4
sw r1 r0 127
li r0 4
li r1 0
li r2 0
li r3 0
li r4 0
li r5 96
li r6 112
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