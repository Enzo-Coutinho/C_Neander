#include "include/cpu.h"
#include "include/instructions.h"

static uint8_t read_byte_from_memory_at_program_counter_and_advance(cpu_t * cpu, memory_t * memory) {
    uint8_t result = read_byte_from_memory(memory, cpu->registers.PC);
    cpu->registers.PC += 1;
    return result;
}

static void write_accumulator_and_update_N_Z(cpu_t * cpu, uint8_t value) {
    cpu->registers.AC = value;
    cpu->flags.N = (uint8_t)((value & 0x80) != 0);
    cpu->flags.Z = (uint8_t)(value == 0);
}

static void fetch(cpu_t * cpu, memory_t * memory) {
    cpu->instruction_register.op_code = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);
}

static void execute(cpu_t * cpu, memory_t * memory) {
    switch(cpu->instruction_register.op_code) {
        case STA: // MEM(addr) <- AC
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);
            write_byte_to_memory(memory, cpu->instruction_register.operand_address, cpu->registers.AC); 
            break;
        case LDA: { // AC <- MEM(addr) (Update N and Z)
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);
            uint8_t value = read_byte_from_memory(memory, cpu->instruction_register.operand_address);
            write_accumulator_and_update_N_Z(cpu, value);
            break;
        }
        case ADD: { // AC <- AC + MEM(addr) (Update N and Z)
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);    
            uint8_t value = read_byte_from_memory(memory, cpu->instruction_register.operand_address);
            write_accumulator_and_update_N_Z(cpu, cpu->registers.AC + value);
            break;
        }
        case OR: { // AC <- AC | MEM(addr) (Update N and Z)
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);
            uint8_t value = read_byte_from_memory(memory, cpu->instruction_register.operand_address);
            write_accumulator_and_update_N_Z(cpu, cpu->registers.AC | value);
            break;
        }
        case AND: { 
            // AC <- AC & MEM(addr) (Update N and Z)
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);    
            uint8_t value = read_byte_from_memory(memory, cpu->instruction_register.operand_address);
            write_accumulator_and_update_N_Z(cpu, cpu->registers.AC & value);
            break;
        }
        case NOT: // AC <- ~AC (Update N and Z)
            write_accumulator_and_update_N_Z(cpu, ~cpu->registers.AC);
            break;
        case JMP:
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);    
            cpu->registers.PC = cpu->instruction_register.operand_address;
            break;
        case JN:
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);    
            if(cpu->flags.N == 1)
                cpu->registers.PC = cpu->instruction_register.operand_address;
            break;
        case JZ:
            cpu->instruction_register.operand_address = read_byte_from_memory_at_program_counter_and_advance(cpu, memory);   
            if(cpu->flags.Z == 1)
                cpu->registers.PC = cpu->instruction_register.operand_address;
            break;
        case NOP:
            cpu->instruction_register.operand_address = 0;
            break;
        case HLT:
            cpu->instruction_register.operand_address = 0;
            cpu->flags.HLT = 1;
            break;
    }
}

void reset_cpu(cpu_t * cpu) {
    cpu->registers.AC = 0;
    cpu->registers.PC = 0;
    cpu->instruction_register.op_code = 0;
    cpu->instruction_register.operand_address = 0;
    cpu->flags.HLT = 0;
    cpu->flags.N = 0;
    cpu->flags.Z = 0;
}

void step(cpu_t * cpu, memory_t * memory) {
    fetch(cpu, memory);
    execute(cpu, memory);
}