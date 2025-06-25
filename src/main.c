#include "op_codes.c"
#include"memory_storage.c"
#include"flags.c"
#include "include/source.h"
#include"helper_functions.c"


int main(int argc,char* argv[]){

    //setup
    signal(SIGINT,handle_interrupt);
    disable_input_buffering();

    //load image file
    if(argc <2){
        printf("usage   lc3 [image file].....\n");
        exit(1);
    }

    for (int j =1; j<argc;j++){
        if(!read_image(argv[j])){
            printf("failed to load image %S",argv[j]);
        }
    }

    //only one conditonal flag shouldbe set at aany givrn time
    reg[R_COND]=FLAG_ZERO;

    //SET PROGRAM COUNTER START POSITION
    enum{PC_Start=0x3000};
    reg[R_PC]=PC_Start;

    int running =1;
    while(running){
        /*fetch instruction*/
        uint16_t instruction = mem_read(reg[R_PC]++);
        uint16_t op_code = instruction >> 12;

        //instruction to handle
        switch(op_code){
            case OP_ADD:{
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
            break;
        }


            case OP_AND:{
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

            break;
        }
            case OP_NOT:{
            uint16_t r0= (instruction >> 9)& 0x7; //destination reg
            uint16_t r1 =(instruction >> 6)& 0x7; //first operand

            reg[r0] = ~(reg[r1]);
            update_flags(r0);
            break;
        }
            case OP_JMP:{ 
            uint16_t r1 = (instruction >> 6) & 0x7;
            reg[R_PC]=reg[r1];
            break;
            }
            case OP_RET:{
            uint16_t r1 = (instruction >> 6) & 0x7;
            reg[R_PC]=reg[R7];
            break;
        }
            case OP_TRAP:{
                running = 0 ;
                break;
            }
          
        }

    }

}