#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/cpu.h"
#include "include/memory.h"
#include "include/instructions.h"

int main() {
    cpu_t cpu;
    memory_t memory;

    reset_cpu(&cpu);
    reset_memory(&memory);

    FILE * file = fopen("test.mem", "rb");

    if(file == NULL)
        return -1;

    uint8_t line[256 * 2]; // 16-bit

    int numberOfBytesRead = fread(line, 1, 256 * 2, file);

    fclose(file);

    if(!numberOfBytesRead) 
        return -2;

    for(int i=4, j=0; i<256 * 2; i+= 2, j++)
        memory.data[j] = line[i];

    print_memory(&memory);

    while(1) {
        step(&cpu, &memory);

        if(cpu.flags.HLT)
            break;
    }

    print_memory(&memory);

    return 0;
}