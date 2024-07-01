#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <cstring>
using namespace std;

#define N 100

typedef int cid_t;
typedef int ctime_t;
struct Car{
    cid_t id;ctime_t time;
    Car():id(0),time(0){}
    Car(cid_t id,ctime_t time):id(id),time(time){}
};

class ParkSystem{
private:
    stack<Car> park;   
    stack<Car> temp;        
    queue<Car> road;   
    bool inqueue[N],instack[N];
    double charge;  
    size_t size;       
public:
    ParkSystem(size_t size,double charge):size(size),charge(charge){
        memset(inqueue,0,sizeof(inqueue));
        memset(instack,0,sizeof(instack));
    }
    void Enter(Car car){
        if(park.size()<size){
            park.push(car);
            instack[car.id]=1;
            cout<<"您的车辆已经停好，在停车场的"<<park.size()<<"号位置\n";
        }else{
            road.push(car);
            inqueue[car.id]=1;
            cout<<"非常抱歉，停车场已满，请进入便道等待\n";
        }
    }  
    void Away(Car car){
        cid_t id=car.id;
        ctime_t awayTime=car.time;
        if(instack[id]){
            while(park.top().id!=id){
                temp.push(park.top());
                park.pop();
            }
            ctime_t arrivalTime=park.top().time;
            double cost=(awayTime-arrivalTime)*charge;
            cout<<"车辆"<<id<<"停车时间为"<<awayTime-arrivalTime<<"小时，应缴纳停车费"<<cost<<"元\n";
            park.pop();
            while(!temp.empty()){
                park.push(temp.top());
                temp.pop();
            }
            while(!road.empty() && !inqueue[road.front().id])
                road.pop();
            if(!road.empty()){
                cout<<"停车场已有空位，请便道上的"<<road.front().id<<"号车进入停车场\n";
                park.push(road.front());
                inqueue[road.front().id]=0;road.pop();
            }
        }else if(inqueue[id]){
            inqueue[id]=0;
            cout<<"便道上的"<<id<<"号车已经离开\n";
        }else{
            cout<<"该的车牌号不在该停车场\n";
        }
    }       
};
void printPage(size_t size,double charge){
        cout<<"欢迎使用停车场管理系统！\n";
        cout<<"本停车场容量为："<<size<<endl;
        cout<<"本停车场收费为："<<charge<<"元/小时\n";
        cout<<"输入规则如下:\n";
        cout<<"1、出入车指示(A,D,E)分别代表到达,离去,结束程序)\n";
        cout<<"2、车牌号码(整数)\n";
        cout<<"3、到达或离开时间(使用0-24整数)\n";
        cout<<"-------------------------------------\n";
}