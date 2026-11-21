#include "include/instructions.h"

#define LENGHT_MEM_FILE ((256 * 2) + 4)

int feed_memory_with_mem_file(const char * file_name, memory_t * memory) {
    FILE * file = fopen(file_name, "rb");

    if(file == NULL)
        return -1;

    uint8_t line[LENGHT_MEM_FILE]; // 16-bit

    int numberOfBytesRead = fread(line, 1, LENGHT_MEM_FILE, file);

    fclose(file);

    if(!numberOfBytesRead) 
        return -2;

    for(int i=4, j=0; j < 256; i+= 2, j++)
        memory->data[j] = line[i];

    return 0;
}