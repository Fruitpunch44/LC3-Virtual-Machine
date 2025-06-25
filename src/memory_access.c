#include "memory_storage.c"
#include"../include/source.h"
#include"memory_mapped_registers.c"
#include"input_buffering.c"


void mem_write(uint16_t address,uint16_t val){
    memory[address]=val;
}

uint16_t mem_read(uint16_t address){
    if(address== MR_KEYBOARD_STATUS){
        if(check_key()){
            memory[MR_KEYBOARD_STATUS]=(1<<15);
            memory[MR_KEYBOARD_DATA]=getchar();
        }
        else{
            memory[MR_KEYBOARD_STATUS]=0;
        }
    }
    return memory[address];
}