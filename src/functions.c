#include "genesis.h"
#include "debug.h"

//Move
void MOV(VM *vm, uint32_t i){
    //Register-Memory
    if(MODE(i) >> 2)
    {
        debug("MOV", "MOV %s [%d]", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = IMM16(i);
    } 
    //Register-IMM32
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("MOV", "MOV %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = prog_read(vm, vm->registers[RPC]++);
    }
    //Register-Register
    else if (MODE(i) & 0x1)
    {
        debug("MOV", "MOV %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] = vm->registers[SR2(i)];
    }
}

//Store
void STR(VM *vm, uint32_t i){}

/********************************************/
//Arithmetics
/********************************************/

//Add
void ADD(VM *vm, uint32_t i){}

//Subtract
void SUB(VM *vm, uint32_t i){}

//Multiply
void MUL(VM *vm, uint32_t i){}

//Divide
void DIV(VM *vm, uint32_t i){}

//Modulus
void MOD(VM *vm, uint32_t i){}

//Shift
void SH(VM *vm, uint32_t i){}