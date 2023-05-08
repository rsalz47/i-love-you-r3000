li r0 0
li r1 59842
sw r1 r0 217
li r1 745483
sw r1 r0 218
li r1 637582
sw r1 r0 219
li r1 274673
sw r1 r0 220
li r1 61220
sw r1 r0 221
li r1 629814
sw r1 r0 222
li r1 690366
sw r1 r0 223
li r1 678201
sw r1 r0 224
li r1 121069
sw r1 r0 225
li r1 396804
sw r1 r0 226
li r1 786458
sw r1 r0 227
li r1 597389
sw r1 r0 228
li r1 940022
sw r1 r0 229
li r1 844543
sw r1 r0 230
li r1 874394
sw r1 r0 231
li r1 174563
sw r1 r0 232
li r1 928686
sw r1 r0 233
li r1 911778
sw r1 r0 234
li r1 335722
sw r1 r0 235
li r1 317180
sw r1 r0 236
li r1 897404
sw r1 r0 237
li r1 45771
sw r1 r0 238
li r1 53795
sw r1 r0 239
li r1 155017
sw r1 r0 240
li r1 80809
sw r1 r0 241
li r1 946657
sw r1 r0 242
li r1 470415
sw r1 r0 243
li r1 86087
sw r1 r0 244
li r1 745413
sw r1 r0 245
li r1 704437
sw r1 r0 246
li r1 88908
sw r1 r0 247
li r1 728767
sw r1 r0 248
li r1 25704
sw r1 r0 249
li r1 738956
sw r1 r0 250
li r1 548102
sw r1 r0 251
li r1 650748
sw r1 r0 252
li r1 688544
sw r1 r0 253
li r1 545196
sw r1 r0 254
li r1 873406
sw r1 r0 255
li r1 415715
sw r1 r0 256
li r1 780218
sw r1 r0 257
li r1 338473
sw r1 r0 258
li r1 178215
sw r1 r0 259
li r1 742542
sw r1 r0 260
li r1 733945
sw r1 r0 261
li r1 960887
sw r1 r0 262
li r1 296066
sw r1 r0 263
li r1 507008
sw r1 r0 264
li r1 338746
sw r1 r0 265
li r1 469295
sw r1 r0 266
li r1 211966
sw r1 r0 267
li r1 336250
sw r1 r0 268
li r1 61009
sw r1 r0 269
li r1 855711
sw r1 r0 270
li r1 530641
sw r1 r0 271
li r1 385496
sw r1 r0 272
li r1 223767
sw r1 r0 273
li r1 728653
sw r1 r0 274
li r1 245322
sw r1 r0 275
li r1 293353
sw r1 r0 276
li r1 770449
sw r1 r0 277
li r1 907546
sw r1 r0 278
li r1 256023
sw r1 r0 279
li r1 345395
sw r1 r0 280
li r1 633004
sw r1 r0 281
li r1 995293
sw r1 r0 282
li r1 398544
sw r1 r0 283
li r1 802249
sw r1 r0 284
li r1 357634
sw r1 r0 285
li r1 397357
sw r1 r0 286
li r1 490018
sw r1 r0 287
li r1 70250
sw r1 r0 288
li r1 917336
sw r1 r0 289
li r1 23006
sw r1 r0 290
li r1 595269
sw r1 r0 291
li r1 275521
sw r1 r0 292
li r1 312323
sw r1 r0 293
li r1 241162
sw r1 r0 294
li r1 9876
sw r1 r0 295
li r1 90846
sw r1 r0 296
li r1 819313
sw r1 r0 297
li r1 214230
sw r1 r0 298
li r1 666421
sw r1 r0 299
li r1 713949
sw r1 r0 300
li r1 412074
sw r1 r0 301
li r1 455020
sw r1 r0 302
li r1 714318
sw r1 r0 303
li r1 817383
sw r1 r0 304
li r1 577055
sw r1 r0 305
li r1 80776
sw r1 r0 306
li r1 209261
sw r1 r0 307
li r1 968421
sw r1 r0 308
li r1 607105
sw r1 r0 309
li r1 684102
sw r1 r0 310
li r1 387773
sw r1 r0 311
li r1 930432
sw r1 r0 312
li r1 27667
sw r1 r0 313
li r1 163882
sw r1 r0 314
li r1 840790
sw r1 r0 315
li r1 232386
sw r1 r0 316
li r2 0
li r3 99
li r7 100
.outerloop beq r2 r3 .exitouter
addi r4 r2 1
.innerloop beq r4 r7 .exitinner
lw r5 r4 217
lw r6 r2 217
blt r6 r5 .exitif
sw r5 r2 217
sw r6 r4 217
.exitif addi r4 r4 1
j .innerloop
.exitinner addi r2 r2 1
j .outerloop
.exitouter hcf