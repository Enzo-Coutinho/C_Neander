#include <stdio.h>
#include "include/cpu.h"
#include "include/memory.h"
#include "include/instructions.h"

int main(int argc, char * argv[]) {
    cpu_t cpu;
    memory_t memory;

    reset_cpu(&cpu);
    reset_memory(&memory);

    int error = feed_memory_with_mem_file(argv[0], &memory);

    if(error) return error;

    print_memory(&memory);

    while(1) {
        step(&cpu, &memory);

        if(cpu.flags.HLT)
            break;
    }

    print_memory(&memory);

    return 0;
}