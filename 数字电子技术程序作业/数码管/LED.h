#ifndef LED
#define LED
#include "mytype.h"
#include <iostream>
using std::cout;
/*
*****
*   *
*****
*   *
*****
*/
void high1(char g[5][6]){
    for(int i=0;i<5;i++)g[0][i]='*';
}
void high2(char g[5][6]){
    for(int i=0;i<3;i++)g[i][4]='*';
}
void high3(char g[5][6]){
    for(int i=2;i<5;i++)g[i][4]='*';
}
void high4(char g[5][6]){
    for(int i=0;i<5;i++)g[4][i]='*';
}
void high5(char g[5][6]){
    for(int i=2;i<5;i++)g[i][0]='*';
}
void high6(char g[5][6]){
    for(int i=0;i<3;i++)g[i][0]='*';
}
void high7(char g[5][6]){
    for(int i=0;i<5;i++)g[2][i]='*';
}

//接收BCD-七段显示译码器的输出并将高电平的相应位置显示
void LEDshow(out7448 Y){
    char g[5][6];
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            g[i][j]=' ';
    void (*highs[7])(char[5][6])={high1,high2,high3,high4,high5,high6,high7};

        
    for(int i=0;i<7;i++){
        if(Y[i]==1)
            highs[i](g);
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            cout<<g[i][j];
        cout<<'\n';
    }
    cout<<'\n';
}

#if defined(_MSC_VER)
    #include <windows.h>
    #define SLEEP(seconds) Sleep(static_cast<DWORD>(seconds * 1000))
#elif defined(__GNUC__) || defined(__clang__)
    #include <unistd.h>
    #define SLEEP(seconds) sleep(seconds)
#endif

#include <cstdlib>
#include <ctime>
void __testLED(){
    out7448 bs[10]{
        out7448("0111111"),out7448("0000110"),out7448("1011011"),
        out7448("1001111"),out7448("1100110"),out7448("1101101"),
        out7448("1111101"),out7448("0000111"),out7448("1111111"),
        out7448("1101111")
    };
    std::srand(std::time(0));
    while(true){
        int num = std::rand() % 10;
        LEDshow(bs[num]);
        SLEEP(2);
    }    
}


#endif