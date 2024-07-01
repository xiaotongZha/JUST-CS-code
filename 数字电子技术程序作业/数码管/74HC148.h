#ifndef _74HC148
#define _74HC148
#include "LogicGate.h"
#include "mytype.h"

//定义74148的功能函数
out74148 func_74148(in74148 I_,bool S_){//I S 均以非形式给出
    out74148 os;
    bool G1=NOT(S_);
    bool G3=NAND({I_[0],I_[1],I_[2],I_[3],I_[4],I_[5],I_[6],I_[7]});
    bool G2=NAND({G1,G3});
    os.Y_[0]=NOR({
        AND({NOT(I_[1]),I_[2],I_[4],G1}),
        AND({NOT(I_[3]),I_[4],I_[6],G1}),
        AND({NOT(I_[5]),I_[6],G1}),
        AND({NOT(I_[7]),G1})
    });
    os.Y_[1]=NOR({
        AND({NOT(I_[2]),I_[4],I_[5],G1}),
        AND({NOT(I_[3]),I_[4],I_[5],G1}),
        AND({NOT(I_[6]),G1}),
        AND({NOT(I_[7]),G1})
    });
    os.Y_[2]=NOR({
        AND({NOT(I_[4]),G1}),
        AND({NOT(I_[5]),G1}),
        AND({NOT(I_[6]),G1}),
        AND({NOT(I_[7]),G1})
    });
    os.Yex_=G2;
    os.Ys_=G3;
    return os;
}
#endif