#ifndef mytype
#define mytype
#include <bitset>
using std::bitset;

//定义bcd8421码类型
typedef bitset<4> bcd8421_t;

struct out74148{
    bitset<3> Y_;//74148的三个输出，取非门
    bool Ys_;//选通输出端，取非门
    bool Yex_;//扩展端，取非门
};

//定义74148的输入类型
typedef bitset<8> in74148;

//定义74148的输出类型
typedef bitset<7> out7448;

#endif