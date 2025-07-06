#include "op_codes.c"
#include"memory_storage.c"
#include"flags.c"
#include "include/source.h"
#include"helper_functions.c"
#include"memory_access.c"
#include"input_buffering.c"
#include"op_code_instruction.c"

void handle_interrupt(int signal){
    restore_input_buffering();
    printf("\n");
    exit(-2);
};

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
                op_add(instruction);
                break;
        }
            case OP_AND:{
                op_and(instruction);
                break;
        }
            case OP_NOT:{
                op_not(instruction);
                break;
        }
            case OP_LD:{ 
                op_LD(instruction);
                break;
            }
            case OP_RET:{
                op_RET(instruction);
                break;
        }
            case OP_LEA:{
                op_LEA(instruction);
                break;
        }
            case OP_LDI:{
                op_LDI(instruction);
                break;
        }
            case OP_LDR:{
                op_LDR(instruction);
                break;
        }
            case OP_ST:{
                op_ST(instruction);
                break;
        }
        case OP_JSR:{
                op_JSRR(instruction);
                break;
        }
            case OP_TRAP:{
                uint16_t Trap_value=op_TRAP(instruction);

                switch(Trap_value){

                    case TRAP_GETC:{
                    reg[R0]=getchar();
                    update_flags(R0);
                    break;
                    }

                    case TRAP_IN:{
                        printf("enter something a character most likely: ");
                        char c =getchar();
                        putc(c,stdout);
                        fflush(stdout);
                        reg[R0] = c;
                        update_flags(R0);
                        break;
                    }
                    case TRAP_PUTSP:{
                        uint16_t*c = memory + reg[R0];
                        while(*c){
                            char character1 = (*c) & 0xff;
                            putc(character1,stdout);
                            char character2 =(*c)>>8;
                            if (character2){
                                putc(character2,stdout);
                                ++c;
                            }
                            fflush(stdout);
                        }

                    }
                    case TRAP_HALT:{
                        puts("STOP");
                        fflush(stdout);
                        running = 0;

                    }
                }



                break;
            }
          
        }

    }

}