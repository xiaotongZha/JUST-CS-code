#include <iostream>
#include "ParkSystem.hpp"
using namespace std;

int main(){
    system("chcp 65001");
    size_t size;double charge;
    cout<<"请输入停车场的最大容量：\n";cin>>size;
    cout<<"请输入停车场的收费标准：\n";cin>>charge;
    system("cls");
    ParkSystem park(size,charge);
    char choice;
    while(1){
        printPage(size,charge);
        cin>>choice;
        switch(choice){
            cid_t id;ctime_t time;
        case 'A':
            cin >> id;cin >> time;
            park.Enter(Car(id,time));
            break;
        case 'D':
            cin >> id;cin >> time;
            park.Away(Car(id,time));
            break;
        case 'E':
            cout<<"bye\n";
            return 0;
        default:
            cout<<"error input\n";
            break;
        system("pause");
        system("cls");
        }
    }
    system("pause");
    return 0;
}

