#ifndef CPU_H
#define CPU_H

#include <inttypes.h>
#include "memory.h"

typedef uint8_t u8;

typedef struct {
    u8 AC : 8;
    u8 PC : 8;
} registers_t;

typedef struct {
    u8 N : 1;
    u8 Z : 1;
    u8 HLT : 1;
} flags_t;

typedef struct {
    u8 op_code : 8;
    u8 operand_address : 8;
} instruction_register_t;

typedef struct {
    registers_t registers;
    flags_t flags;
    instruction_register_t instruction_register;
} cpu_t;

void reset_cpu(cpu_t * cpu);
void step(cpu_t * cpu, memory_t * memory);

#endif
