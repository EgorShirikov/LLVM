bb0:
    alloca x1 1200
    alloca x2 1200
    geti x3 x3 0
    simInit
bb1:
    xor x4 x4 x4
    simRand x5
    get x6 x2 x5
    store x5 x6
    inc_eqi x4 x4 4800
    bnz x4 bb2 bb1
bb2:
    simEvent x7
    bnz x7 bb3 bb13
bb3:
    get x8 x1 0
bb4:
    xor x9 x9 x9
    xor x10 x10 x10
    store x11 x10
    divi x10 x10 80
    muli x10 x10 80
    store x12 x11
    sub x11 x11 10
    store x15 x11
    addi x12 x11 -1
    addi x11 x11 -1
    store x16 x11
bb5:
    xor x11 x11 x11
    ugt x13 x13 59
    eq  x14 x14 x12
    muli x12 x12 80
    store x19 x12
    br bb7
bb6:
    addi x12 x12 1
    sgt x12 x15
    bnz x12 bb10 bb5
bb7:
    store x17 x16
    ugt x16 x16 79
    or  x13 x13 x16
    eq  x17 x16 x11
    and x18 x14 x17
    or  x13 x13 x18
    bnz x13 bb9 bb8
bb8:
    add x17 x17 x19
    zext x17 64
    gep x20 x3 x17
    store x21 x20
    add x11 x21 x11
bb9:
    addi x22 x16 1
    sgt x23 x16 x15
    bnz x23 block2 block3
bb10:
    get x24 x3 x10
    store x25 x24
    eqi x26 x25 0
    eqi x27 x11 3
    andi x28 x11 -2
    eqi x29 x28 2
    get x31 x8 x9
    store x30 x31
    addi x9 x9 1
    addi x10 x10 1
    eqi x32 x9 4800
    bnz x32 bb11 bb4
bb11:
    xor x33 x33 x33
    get x34 x3 x33
    store x35 x34
    muli x35 x35 65280
    addi x36 x35 -16777216
    simSetPixel x35 x36
    addi x33 x33 1
    eqi x34 x33 4800
    bnz x34 bb12 bb11
bb12:
    simFlush
    simEvent x35
    bnz x35 bb4 bb13
bb13:
    simExit
    ret 0












