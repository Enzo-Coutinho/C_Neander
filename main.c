#include <stdio.h>
#include "include/cpu.h"
#include "include/memory.h"
#include "include/instructions.h"

int main() {
    cpu_t cpu;
    memory_t memory;

    reset_cpu(&cpu);
    reset_memory(&memory);

    memory.data[0x00] = LDA;
    memory.data[0x01] = 0xF0;
    memory.data[0x02] = ADD;
    memory.data[0x03] = 0xF1;
    memory.data[0x04] = STA;
    memory.data[0x05] = 0xF2;
    memory.data[0x06] = HLT;
    memory.data[0xF0] = 0x01;
    memory.data[0xF1] = 0x01;

    while(1) {
        step(&cpu, &memory);
    
        if(cpu.flags.HLT)
            break;
    }

    print_memory(&memory);

    return 0;
}