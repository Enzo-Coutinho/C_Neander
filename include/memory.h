#ifndef MEMORY_H
#define MEMORY_H

#include <inttypes.h>

#define MEM_LENGHT 256

typedef struct {
    uint8_t data[MEM_LENGHT];
    uint8_t read_count;
    uint8_t write_count;
} memory_t;

void reset_memory(memory_t * memory);
uint8_t read_byte_from_memory(memory_t * memory, uint8_t address);
void write_byte_to_memory(memory_t * memory, uint8_t address, uint8_t value);
void print_memory(memory_t * memory);

#endif