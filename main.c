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

    FILE * file = fopen("program.txt", "r");

    if(file == NULL)
        return -1;

    char line[256];
    uint8_t line_number = 0;

    while(fgets(line, sizeof(line), file) != NULL) {

        char *comment_start = strchr(line, ';');
        if (comment_start != NULL) {
            *comment_start = '\0';
        }

        line[strcspn(line, " \r\n")] = '\0';

        printf("Line %d instruction: '%s'\n", line_number, line);

        long int number = 0;

        if (line[0] == '0' || (line[1] == 'x' && line[1] == 'X')) {
            number = strtol(line, NULL, 16);
        }

        printf("Valor: %ld (0x%lx)\n", number, number);

        char * instructions[11] = {"NOP", "STA", "LDA", "ADD", "OR", "AND", "NOT", "JMP", "JN", "JZ", "HLT"};
        uint8_t instructions_int[11] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x80, 0x90, 0xA0, 0xF0};

        if(!number) {
            for(int i=0; i<11; i++) {
                if(!strcmp(line, instructions[i])) {
                    memory.data[line_number] = instructions_int[i];
                    break;
                }
            }
        } else {
            memory.data[line_number] = number;
        }   

        line_number++;
    }

    print_memory(&memory);

    while(1) {
        step(&cpu, &memory);
    
        if(cpu.flags.HLT)
            break;
    }

    print_memory(&memory);

    return 0;
}