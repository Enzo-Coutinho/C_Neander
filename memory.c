#include "include/memory.h"

void reset_memory(memory_t * memory) {
    for(int i=0; i < MEM_LENGHT; i++)
        memory->data[i] = 0;
    memory->read_count = memory->write_count = 0;
}

uint8_t read_byte_from_memory(memory_t * memory, uint8_t address) {
    uint8_t value = memory->data[address];
    memory->read_count++;
    return value;
}

void write_byte_to_memory(memory_t * memory, uint8_t address, uint8_t value) {
    memory->data[address] = value;
    memory->write_count++;
}