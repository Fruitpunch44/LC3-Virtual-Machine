#include "register.c"
#include <stdio.h>
#include"include/source.h"
#define max_mem_size (1 << 16)
uint16_t memory[max_mem_size];// 65536 location
uint16_t reg[R_COUNT];