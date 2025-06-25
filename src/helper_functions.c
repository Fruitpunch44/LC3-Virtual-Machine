#include"memory_storage.c"
#include"flags.c"

__uint16_t sign_extend(__uint16_t x, int bit_count){
    if((x >>(bit_count-1)) & 1){
        x |= (0xFFF << bit_count);
    }
    return x;
}

/*Check the flag anytime a value is written
to the register and update the flags to indicate it's sign*/
void update_flags(__uint16_t r){
    if(reg[r]==0){
        reg[R_COND]=FLAG_ZERO;
    }
    else if (reg[r]>>15)
    {
        reg[R_COND]=FLAG_NEG;
    }
    else {
        reg[R_COND]=FLAG_POS;
    }
    
}