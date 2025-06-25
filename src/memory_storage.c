#include "register.c"
#include <stdio.h>
#define max_mem_size (1 << 16)
__uint16_t memory[max_mem_size];// 65536 location
__uint16_t reg[R_COUNT];