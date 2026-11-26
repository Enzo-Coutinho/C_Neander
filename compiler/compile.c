#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    FILE * file = fopen(argv[0], "r");

    if(file == NULL)
        return -1;

    char line[256];
    uint8_t formating_values[(256 * 2) + 4] = {0x03, 0x4E, 0x44, 0x52};

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

        const uint8_t line_number = strtol(line_number_text, NULL, 16);
        const int mem_index = 4 + (line_number * 2);

        const char *instructions[11] = {"NOP", "STA", "LDA", "ADD", "OR", "AND", "NOT", "JMP", "JN", "JZ", "HLT"};
        const uint8_t instructions_int[11] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x80, 0x90, 0xA0, 0xF0};

        bool is_instruction = false;

        for (int i = 0; i < 11; i++) {
            if (strcmp(constant_or_op_code_text, instructions[i]) == 0) {
                formating_values[mem_index] = instructions_int[i];
                is_instruction = true;
                break;
            }
        }

        if (!is_instruction) {
            formating_values[mem_index] = (uint8_t)strtol(constant_or_op_code_text, NULL, 16);
        }

        if(total_readings == 3 && line_number < 0xFF) {
            uint8_t address = strtol(address_text, NULL, 16);
            const int next_mem_index = 4 + ((line_number + 1) * 2);
            formating_values[next_mem_index] = address;
        }

    }

    fclose(file);

    FILE * compiled_file = fopen("program.mem", "wb");

    if(compiled_file == NULL)
        return -1;

    fwrite(formating_values, sizeof(uint8_t), (256 * 2) + 4, compiled_file);
    fclose(compiled_file);

    return 0;
}