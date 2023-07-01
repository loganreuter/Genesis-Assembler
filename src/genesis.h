#ifndef GENESIS_H
#define GENESIS_H

#include <stdint.h>

//Size of memory and program
#define SIZE (1 << 16)

//Number of operations
#define NOPS (16)

//Extract Op Code
#define OpCode(i) ((i) >> 26)

// Extract Mode
#define MODE(i) (((i) >> 23) & 0x7)

// Extract Source #1
#define SR1(i) (((i) >> 19) & 0x7) 

//Extract Source #2
#define SR2(i) ((i) & 0x7) 

//Extract Immediate 16
#define IMM16(i) ((i) & 0xffff)

//Little Endian Encoding
#define ENCODE(i, s) (((i) >> (s * 8)) & 0xFF)

typedef void (*op_ex_f)(uint32_t instruction);
typedef struct VM VM;
typedef enum regist reg;

//Registers
enum regist
{
    EAX,
    EBX,
    ECX,
    EDX,
    EEX,
    EFX,
    RPC,
    ESP,
    EBP,
    ESI,
    EDI,
    FLAG,
    REG_CNT
};
//Returns the name of the register
char *name(enum regist r){
    switch (r){
        case EAX:
            return "EAX";
        case EBX:
            return "EBX";
        case ECX:
            return "ECX";
        case EDX:
            return "EDX";
        case EFX:
            return "EFX";
        case RPC:
            return "RPC";
        case ESP:
            return "ESP";
        case EBP:
            return "EBP";
        case ESI:
            return "ESI";
        case EDI:
            return "EDI";
        case FLAG:
            return "FLAG";
        default:
            return "INVALID";
    }
}

//flags for FLAG register
enum flags
{
    CF = 1 << 0, //Carry flag
    PF = 1 << 2, //Parity flag
    AF = 1 << 4, //Auxiliary flag
    ZF = 1 << 6, //Zero flag
    SF = 1 << 7, //Sign flag
    TF = 1 << 8, //
    IF = 1 << 9, //Interrupt flag
    DF = 1 << 10,//
    OF = 1 << 11 //Overflow flag
};

struct VM
{
    uint32_t program[SIZE];
    uint32_t registers[REG_CNT];
    uint8_t memory[SIZE];
};

op_ex_f op_ex[NOPS];

VM* createVM();

void update_flag(VM *vm, reg r);

uint32_t prog_read(VM *vm, uint16_t address);

uint8_t mem_read(VM *vm, uint16_t address);
uint32_t mem_readn(VM *vm, uint16_t address, int size);
void mem_write(VM *vm, uint16_t address, uint8_t val);

void clear(VM *vm);

void start(VM *vm, uint32_t *ops, int size);

#endif