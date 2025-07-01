//op codes

enum{
    OP_ADD,//addition
    OP_AND,//bitwise logical and
    OP_BR = 0,//conditonal branch
    OP_JMP,//jump 
    OP_RET,//Return from subroutine
    OP_JSR,//Jump to Subroutine
    OP_LD,//Load
    OP_LDI,//Load Indirect
    OP_LDR,//Load Base+offset
    OP_LEA,//Load Effective Address
    OP_NOT,//Bit-Wise Complement
    OP_RTI,//Return from Interrupt
    OP_ST,//Store
    OP_STI,//Store Indirect
    OP_STR,//Store Base+offset
    OP_TRAP//System Call

    //might not do all i'm lazy

};