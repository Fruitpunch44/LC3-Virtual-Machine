#include "op_codes.c"
#include "include/source.h"
#include"helper_functions.c"


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
    reg[r0] = ~(reg[r1]);
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