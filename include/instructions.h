#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

enum Instructions {
    NOP = 0x00,
    STA = 0x01,
    LDA = 0x02,
    ADD = 0x03,
    OR = 0x04,
    AND = 0x05,
    NOT = 0x06,
    JMP = 0x08,
    JN = 0x09,
    JZ = 0x0A,
    HLT = 0x0F,
};

#endif
