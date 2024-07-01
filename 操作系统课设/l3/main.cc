#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <deque>
#include "util.hpp"
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
using namespace std;

#define N 20

mutex mtx;
condition_variable cond;
bool run=false;
deque<char>buffer;
bool pro_st[N];
bool con_st[N];
int pro_sp=3;
int con_sp=7;
void producer(int id,char fruit){
    while(true){
        unique_lock<mutex>lk(mtx);
        pro_st[id]=0;
        cond.wait(lk,[](){
            return run and buffer.size()<20;
        });
        pro_st[id]=1;
        buffer.push_back(fruit);
        printf("producer %d put %c\n",id,fruit);
        lk.unlock();
        cond.notify_all();
        SLEEP(randomInt(pro_sp-2,pro_sp+2)*1000);
    }
}
void consumer(int id,char fruit){
    while(true){
        unique_lock<mutex>lk(mtx);
        con_st[id]=0;
        cond.wait(lk,[&fruit](){
            return run and buffer.size()>0 and buffer.front()==fruit;
        });
        con_st[id]=1;
        buffer.pop_front();
        printf("consumer %d get %c\n",id,fruit);
        lk.unlock();
        cond.notify_all();
        SLEEP(randomInt(con_sp-2,con_sp+2)*1000);
    }
}

int main(){
    system("chcp 65001");
    unique_ptr<thread> pro_th[N];
    unique_ptr<thread> con_th[N];
    for(int i=0;i<N;i++){
        pro_th[i]=make_unique<thread>(producer,i,"ao"[i*2<N]);
    }
    for(int i=0;i<N;i++){
        con_th[i]=make_unique<thread>(consumer,i,"ao"[i*2<N]);
    }

    while (true){
        printf("按r进入运行模式,按p进入暂停模式\n");
        char c1;cin>>c1;
        if(c1=='r'){
            mtx.lock();
            run=true;
            mtx.unlock();
            cond.notify_all();
        }else if(c1=='p'){
            mtx.lock();
            run=false;
            while(true){
                printf("暂停模式,按w查看,按m修改速度,按q退出\n");
                char c2;cin>>c2;
                if(c2=='w'){
                    print(buffer);
                    printf("producer running:"); for(int i=0;i<N;i++) if(pro_st[i]) printf("%d ",i); printf("\n");
                    printf("producer blocking:"); for(int i=0;i<N;i++) if(!pro_st[i]) printf("%d ",i); printf("\n");
                    printf("consumer running:"); for(int i=0;i<N;i++) if(con_st[i]) printf("%d ",i); printf("\n");
                    printf("consumer blocking:"); for(int i=0;i<N;i++) if(!con_st[i]) printf("%d ",i); printf("\n");
                }else if(c2=='m'){
                    printf("当前生产速度:%d 消费速度:%d\n",pro_sp,con_sp);
                    printf("输入两个3~10整数表示生产速度,消费速度(速度越小越快)\n");
                    cin>>pro_sp>>con_sp;
                }else if(c2=='q'){
                    break;
                }
            }
            mtx.unlock();
        }
    }
    

    for(int i=0;i<N;i++){
        pro_th[i]->join();
        con_th[i]->join();
    }
    return 0;
}