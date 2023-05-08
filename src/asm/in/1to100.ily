li r0 0
li r1 87
sw r1 r0 220
li r1 12
sw r1 r0 221
li r1 39
sw r1 r0 222
li r1 51
sw r1 r0 223
li r1 55
sw r1 r0 224
li r1 40
sw r1 r0 225
li r1 26
sw r1 r0 226
li r1 84
sw r1 r0 227
li r1 82
sw r1 r0 228
li r1 18
sw r1 r0 229
li r1 96
sw r1 r0 230
li r1 1
sw r1 r0 231
li r1 31
sw r1 r0 232
li r1 73
sw r1 r0 233
li r1 64
sw r1 r0 234
li r1 100
sw r1 r0 235
li r1 89
sw r1 r0 236
li r1 19
sw r1 r0 237
li r1 25
sw r1 r0 238
li r1 59
sw r1 r0 239
li r1 69
sw r1 r0 240
li r1 49
sw r1 r0 241
li r1 66
sw r1 r0 242
li r1 44
sw r1 r0 243
li r1 67
sw r1 r0 244
li r1 78
sw r1 r0 245
li r1 11
sw r1 r0 246
li r1 36
sw r1 r0 247
li r1 47
sw r1 r0 248
li r1 15
sw r1 r0 249
li r1 10
sw r1 r0 250
li r1 93
sw r1 r0 251
li r1 61
sw r1 r0 252
li r1 85
sw r1 r0 253
li r1 99
sw r1 r0 254
li r1 74
sw r1 r0 255
li r1 56
sw r1 r0 256
li r1 70
sw r1 r0 257
li r1 42
sw r1 r0 258
li r1 17
sw r1 r0 259
li r1 37
sw r1 r0 260
li r1 53
sw r1 r0 261
li r1 46
sw r1 r0 262
li r1 20
sw r1 r0 263
li r1 5
sw r1 r0 264
li r1 60
sw r1 r0 265
li r1 7
sw r1 r0 266
li r1 62
sw r1 r0 267
li r1 52
sw r1 r0 268
li r1 4
sw r1 r0 269
li r1 75
sw r1 r0 270
li r1 13
sw r1 r0 271
li r1 65
sw r1 r0 272
li r1 98
sw r1 r0 273
li r1 33
sw r1 r0 274
li r1 35
sw r1 r0 275
li r1 83
sw r1 r0 276
li r1 30
sw r1 r0 277
li r1 94
sw r1 r0 278
li r1 71
sw r1 r0 279
li r1 27
sw r1 r0 280
li r1 86
sw r1 r0 281
li r1 95
sw r1 r0 282
li r1 32
sw r1 r0 283
li r1 23
sw r1 r0 284
li r1 92
sw r1 r0 285
li r1 54
sw r1 r0 286
li r1 2
sw r1 r0 287
li r1 16
sw r1 r0 288
li r1 79
sw r1 r0 289
li r1 57
sw r1 r0 290
li r1 6
sw r1 r0 291
li r1 21
sw r1 r0 292
li r1 80
sw r1 r0 293
li r1 45
sw r1 r0 294
li r1 48
sw r1 r0 295
li r1 58
sw r1 r0 296
li r1 77
sw r1 r0 297
li r1 9
sw r1 r0 298
li r1 50
sw r1 r0 299
li r1 41
sw r1 r0 300
li r1 28
sw r1 r0 301
li r1 38
sw r1 r0 302
li r1 68
sw r1 r0 303
li r1 90
sw r1 r0 304
li r1 3
sw r1 r0 305
li r1 97
sw r1 r0 306
li r1 24
sw r1 r0 307
li r1 22
sw r1 r0 308
li r1 76
sw r1 r0 309
li r1 63
sw r1 r0 310
li r1 81
sw r1 r0 311
li r1 14
sw r1 r0 312
li r1 72
sw r1 r0 313
li r1 29
sw r1 r0 314
li r1 91
sw r1 r0 315
li r1 88
sw r1 r0 316
li r1 43
sw r1 r0 317
li r1 34
sw r1 r0 318
li r1 8
sw r1 r0 319
li r2 0
li r3 99
li r7 100
.outerloop beq r2 r3 .exitouter
addi r4 r2 1
.innerloop beq r4 r7 .exitinner
lw r5 r4 220
lw r6 r2 220
blt r6 r5 .exitif
sw r5 r2 220
sw r6 r4 220
.exitif addi r4 r4 1
j .innerloop
.exitinner addi r2 r2 1
j .outerloop
.exitouter hcf