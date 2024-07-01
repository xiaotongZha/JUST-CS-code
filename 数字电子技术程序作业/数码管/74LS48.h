#ifndef _74LS48
#define _74LS48

#include "mytype.h"
#include "LogicGate.h"

//定义BCD-七段显示译码器的功能函数
out7448 func_7448(bcd8421_t A){
    out7448 Y;
    Y[0]=AND({
        NOT(AND({A[1],A[3]})),
        NOT(AND({NOT(A[0]),A[2]})),
        NOT(AND({A[0],NOT(A[1]),NOT(A[2]),NOT(A[3])})),
    });
    Y[1]=AND({
        NOT(AND({A[1],A[3]})),
        NOT(AND({A[0],NOT(A[1]),A[2]})),
        NOT(AND({NOT(A[0]),A[1],A[2]}))
    });
    Y[2]=AND({
        NOT(AND({A[2],A[3]})),
        NOT(AND({NOT(A[0]),A[1],NOT(A[2])})),
    });
    Y[3]=AND({
        NOT(AND({A[0],NOT(A[1]),NOT(A[2])})),
        NOT(AND({NOT(A[0]),NOT(A[1]),A[2]})),
        NOT(AND({A[0],A[1],A[2]}))
    });
    Y[4]=AND({
        NOT(A[0]),
        NOT(AND({NOT(A[1]),A[2]})),
    });
    Y[5]=AND({
        NOT(AND({A[0],A[1]})),
        NOT(AND({A[1],NOT(A[2])})),
        NOT(AND({A[0],NOT(A[2]),NOT(A[3])}))
    });
    Y[6]=AND({
        NOT(AND({A[0],A[1],A[2]})),
        NOT(AND({NOT(A[1]),NOT(A[2]),NOT(A[3])}))
    });
    return Y;
}

#endif