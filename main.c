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

    while(fgets(line, sizeof(line), file) != NULL) {

        char *comment = strchr(line, ';');
        if (comment != NULL) {
            *comment = '\0';
        }

        char line_number_text[5] = {0};
        char constant_or_op_code_text[5]     = {0};
        char address_text[5]     = {0};

        int total_readings = sscanf(line, "%4s %4s %4s", line_number_text, constant_or_op_code_text, address_text);

        if (total_readings < 2) {
            continue;
        }

        uint8_t line_number = strtol(line_number_text, NULL, 16);


        const char *instructions[11] = {"NOP", "STA", "LDA", "ADD", "OR", "AND", "NOT", "JMP", "JN", "JZ", "HLT"};
        const uint8_t instructions_int[11] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x80, 0x90, 0xA0, 0xF0};

        bool is_instruction = false;

        for (int i = 0; i < 11; i++) {
            if (strcmp(constant_or_op_code_text, instructions[i]) == 0) {
                memory.data[line_number] = instructions_int[i];
                is_instruction = true;
                break;
            }
        }

        if (!is_instruction) {
            memory.data[line_number] = (uint8_t)strtol(constant_or_op_code_text, NULL, 16);
        }

        if(total_readings == 3 && line_number < 0xFF) {
            uint8_t address = strtol(address_text, NULL, 16);
            memory.data[line_number + 1] = address;
        }

    }

    fclose(file);

    print_memory(&memory);

    while(1) {
        step(&cpu, &memory);

        if(cpu.flags.HLT)
            break;
    }

    print_memory(&memory);

    return 0;
}