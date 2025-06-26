#include "op_codes.c"
#include "include/source.h"
#include"helper_functions.c"
#include"memory_access.c"


void op_add(uint16_t instruction){
    //destination register
            uint16_t r0 = (instruction >> 9) & 0x7;

            //firdt operand
            uint16_t r1 =(instruction >> 6 ) & 0x7;
            //if we are in immediate mode
            uint16_t imm_flag = (instruction >> 5) & 0x1;

            if(imm_flag){
                uint16_t imm5=sign_extend(instruction & 0x1F,5);
                reg[r0]=reg[r1]+imm5;
            }
            else{
                uint16_t r2 =instruction & 0x7;
                reg[r0]=reg[r1]+reg[r2];
            }
            update_flags(r0);

}

void op_not(uint16_t instruction){
    uint16_t r0= (instruction >> 9)& 0x7; //destination reg
    uint16_t r1 =(instruction >> 6)& 0x7; //first operand
    reg[r0] = ~(reg[r1]);//not operation
    update_flags(r0);
}

void op_and(uint16_t instruction){
      uint16_t r0= (instruction >> 9)& 0x7; //destination reg
      uint16_t r1 =(instruction >> 6)& 0x7; //first operand
      uint16_t imm_flag =(instruction >> 5 )& 0x1; //imm flag
      if (imm_flag){
        uint16_t imm5=sign_extend(instruction & 0x1F,5);
        reg[r0]= reg[r1] & imm5;
    }
    else{
        uint16_t r2 =instruction & 0x7;
        reg[r0]= reg[r1] & reg[r2];
    }
    update_flags(r0);

}

void op_jmp(uint16_t instruction){
    uint16_t r1 = (instruction >> 6) & 0x7; //destination register
    reg[R_PC] = reg[r1]; //set program counter to the value in the register
}

void op_ret(uint16_t instruction){
    reg[R_PC] = reg[R7]; //return to the address in R7
}

void op_LD(uint16_t instructions){
    uint16_t r0=(instructions>>9) & 0x7 ;//
    uint16_t pc_offset=sign_extend(instructions & 0x1FF,9);
    reg[r0]=mem_read(reg[R_PC]+ pc_offset);
    update_flags(r0);
}

void op_LDR(uint16_t instruction){
    uint16_t r0=(instruction>>9) & 0x7;
    uint16_t r1=(instruction>>6) & 0x7;
    uint16_t offset=sign_extend(instruction & 0x3F,6);
    reg[r0]=mem_read(reg[r1]+offset);
    update_flags(r0);

}

void op_LDI(uint16_t instruction){
    uint16_t r0=(instruction>>9) & 0x7;
    uint16_t pc_offset=sign_extend(instruction & 0x1FF,9);
    reg[r0]=mem_read(mem_read(reg[R_PC]+pc_offset));
    update_flags(r0);

}
void op_LEA(uint16_t instruction){
    uint16_t r0=(instruction>>9) & 0x7;
    uint16_t pc_offset=sign_extend(instruction & 0x1FF,9);
    reg[r0]=reg[R_PC]+pc_offset;
    update_flags(r0);

}
void op_ST(uint16_t instruction){
    uint16_t r0=(instruction>>9) & 0x7;
    uint16_t pc_offset=sign_extend(instruction & 0x1FF,9);
    reg[r0]=mem_write(reg[R_PC]+pc_offset,reg[r0]);
    update_flags(r0);
}

void op_JSRR(uint16_t instruction){
    reg[R7]=reg[R_PC];
    uint16_t long_flag= (instruction >> 11) & 0x1;
    if(long_flag == 0){
        uint16_t r1 =(instruction >> 6) & 0x7;
        reg[R_PC] = reg[r1]; /* JSRR */
    }
    else{
        uint16_t pc_offset=sign_extend(instruction & 0x7FF,11);
        reg[R_PC]+=pc_offset; /* JSR */
    }
    update_flags(reg[R7]);
}