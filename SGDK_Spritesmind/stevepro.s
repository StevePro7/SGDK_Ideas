    .globl	steveproreset
steveproreset:
    move   #0x2700,%sr
    move.l (0),%a7
    move.l (4),%a0
    jmp    (%a0)
