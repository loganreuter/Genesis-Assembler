#include "genesis.h"
#include "debug.h"

//Move
void MOV(VM *vm, uint32_t i)
{
    //Register-Memory
    if(MODE(i) >> 2)
    {
        debug("MOV", "MOV %s [%Xh]", name(SR1(i)), IMM16(i));
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
void STR(VM *vm, uint32_t i)
{   
    //Memory-Register
    if(MODE(i) >> 2)
    {
        debug("STR", "STR [%Xh] %s", IMM16(i), SR1(i));
        for(uint16_t j = 0; j < 5; j++){
            mem_write(vm, IMM16(i) + j, ENCODE(vm->registers[SR1(i)], j));
        }
    }
    //Memory-IMM32
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("STR", "STR [%Xh] %Xh", IMM16(i), prog_read(vm, vm->registers[RPC]));
        for(uint16_t j = 0; j < 5; j++){
            mem_write(vm, IMM16(i) + j, ENCODE(vm->registers[RPC], j));
        }
        vm->registers[RPC]++;
    }
    //Memory-Memory
    else if (MODE(i) & 0x1)
    {
        debug("STR", "STR [%Xh] [%Xh]", IMM16(i), prog_read(vm, vm->registers[RPC]));
        mem_write(vm, IMM16(i), mem_read(vm, prog_read(vm, vm->registers[RPC]++)));
    }
}

/********************************************/
//Arithmetics
/********************************************/

//Add
void ADD(VM *vm, uint32_t i)
{
    //INC
    if(MODE(i) >> 2)
    {
        debug("ADD", "INC %s", name(SR1(i)));
        vm->registers[SR1(i)]++;
    }
    //IADD
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("ADD", "IADD %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] + prog_read(vm, vm->registers[RPC]++);
    }
    //ADD
    else if (MODE(i) & 0x1)
    {
        debug("ADD", "ADD %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] + vm->registers[SR2(i)];
    }
    update_flag(vm, SR1(i));
}

//Subtract
void SUB(VM *vm, uint32_t i)
{
    //DEC
    if(MODE(i) >> 2)
    {
        debug("SUB", "DEC %s", name(SR1(i)));
        vm->registers[SR1(i)]--;
    }
    //ISUB
    else if ((MODE(i) >> 1) & 0x1)
    {
        debug("SUB", "ISUB %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] - prog_read(vm, vm->registers[RPC]++);
    }
    //SUB
    else if (MODE(i) & 0x1)
    {
        debug("SUB", "SUB %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] - vm->registers[SR2(i)];
    }
    update_flag(vm, SR1(i));
}

//Multiply
void MUL(VM *vm, uint32_t i)
{
    //IMUL
    if((MODE(i) >> 1) & 0x1)
    {
        debug("MUL", "IMUL %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] * prog_read(vm, vm->registers[RPC]++);
    }
    //MUL
    else if (MODE(i) & 0x1)
    {
        debug("MUL", "MUL %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] * vm->registers[SR2(i)];
    }
}

//Divide
void DIV(VM *vm, uint32_t i)
{
    //IDIV
    if((MODE(i) >> 1) & 0x1)
    {
        debug("DIV", "IDIV %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] / prog_read(vm, vm->registers[RPC]++);
    }
    //DIV
    else if (MODE(i) & 0x1)
    {   
        debug("DIV", "DIV %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] / vm->registers[SR2(i)];
    }

    update_flag(vm, SR1(i));
}

//Modulus
void MOD(VM *vm, uint32_t i)
{
    //IMOD
    if((MODE(i) >> 1) & 0x1)
    {
        debug("MOD", "IMOD %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] % prog_read(vm, vm->registers[RPC]++);
    }
    else if(MODE(i) & 0x1)
    {
        debug("MOD", "MOD %s %s", name(SR1(i)), name(SR2(i)));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] % vm->registers[SR2(i)];
    }

    update_flag(vm, SR1(i));
}

//Shift
void SH(VM *vm, uint32_t i)
{
    //SHR
    if((MODE(i) >> 1) & 0x1)
    {
        debug("SH", "SHR %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] >> prog_read(vm, vm->registers[RPC]++);
    } 
    //SHL
    else if(MODE(i) & 0x1)
    {
        debug("SH", "SHL %s %Xh", name(SR1(i)), prog_read(vm, vm->registers[RPC]));
        vm->registers[SR1(i)] = vm->registers[SR1(i)] << prog_read(vm, vm->registers[RPC]++);
    }
}

/********************************************/
// Logical
/********************************************/

void AND(VM *vm, uint32_t i){}

void OR(VM *vm, uint32_t i){}

void XOR(VM *vm, uint32_t i){}

void TEST(VM *vm, uint32_t i){}

void NOT(VM *vm, uint32_t i){}

/********************************************/
// Control Flow
/********************************************/

void CMP(VM *vm, uint32_t i){}

void JMP(VM *vm, uint32_t i){}

void JUMP(VM *vm, uint32_t i){}

/********************************************/
// Stack
/********************************************/

void PUSH(VM *vm, uint32_t i){}

void POP(VM *vm, uint32_t i){}

void CALL(VM *vm, uint32_t i){}

void RET(VM *vm, uint32_t i){}

/********************************************/
// Interrupt
/********************************************/

void INT(VM *vm, uint32_t i){}