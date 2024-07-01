#ifndef LogicGate
#define LogicGate
#include <initializer_list>
using std::initializer_list;
//非门
bool NOT(bool f){
    return !f;
}
//与门
bool AND(initializer_list<bool>il){
    for(bool f:il)
        if(f==0)
            return 0;
    return 1;
}
//或门
bool OR(initializer_list<bool>il){
    for(bool f:il)
        if(f==1)
            return 1;
    return 0;
}
//与非门
bool NAND(initializer_list<bool>il){
    return NOT(AND(il));
}
//或非门
bool NOR(initializer_list<bool>il){
    return NOT(OR(il));
}
#endif
