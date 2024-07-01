#include "74HC148.h"
#include "74LS48.h"
#include "LogicGate.h"
#include "LED.h"

using namespace std;

//组合两块74148译码器实现10-4线译码器
bcd8421_t to_bcd8421(in74148 highI_,in74148 lowI_){
    out74148 highOut=func_74148(highI_,0);
    out74148 lowOut=func_74148(lowI_,0);
    bcd8421_t Z_;
    Z_[0]=AND({lowOut.Y_[0],highOut.Y_[0]});
    Z_[1]=AND({lowOut.Y_[1],highOut.Y_[1]});
    Z_[2]=AND({lowOut.Y_[2],highOut.Y_[2]});
    Z_[3]=highOut.Yex_;
    return Z_;
}

void solve(string s){
    s.insert(0,string("000000"));
    //取补码形式
    for(char &c:s)
        c = c=='1'?'0':'1';
    //分割为高低位输入
    in74148 highI_(s.substr(0,8));
    in74148 lowI_(s.substr(8,16));

    //得到bcd编码
    bcd8421_t bcd_code=~to_bcd8421(highI_,lowI_);

    //使用BCD-七段显示译码器进行译码并将结果显示
    out7448 Y=func_7448(bcd_code);
    LEDshow(Y);
}

//测试代码,按逆序每隔一秒输出一个数
void test(){
    int i=0;
    while(true){
        if(i==10)
            i=0;
        string s="0000000000";
        s[i]='1';
        solve(s);
        SLEEP(1);
        i++;
    }
}


int main(){
    // string s;
    // cin>>s;
    // solve(s);
    test();
    return 0;
}