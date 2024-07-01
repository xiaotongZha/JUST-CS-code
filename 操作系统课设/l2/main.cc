#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "sche/PCB.hpp"
#include "sche/RoundRobin.hpp"
#include "sche/StaticPriority.hpp"
#include "sche/ShortJob.hpp"
#include "sche/FirstServer.hpp"

#define RAND_INT(l,r) (rand()%(r-l)+l)
#include "util.hpp"
void report(PCBList &plist,std::map<PCB*,int>em){
    std::vector<int> et(plist.size());
    for(int i=0;i<plist.size();i++)
        et[i]=em[plist[i]];
    std::vector<int> ft(plist.size());
    std::vector<double> aft(plist.size());
    double sum_ft=0,sum_aft=0;
    for(int i=0;i<plist.size();i++) ft[i]=et[i]-plist[i]->startTime(),sum_ft+=ft[i];
    for(int i=0;i<plist.size();i++) aft[i]=ft[i]*1.0/plist[i]->serveTime(),sum_aft+=aft[i];
    std::cout<<"########################\npid\tend\tTAT\tWTAT\n";
    for(int i=0;i<plist.size();i++) std::cout<<i<<'\t'<<et[i]<<'\t'<<ft[i]<<'\t'<<aft[i]<<'\n';
    std::cout<<"avg TAT:"<<sum_ft/plist.size()<<"\navg WTAT:"<<sum_aft/plist.size()<<'\n';
}
void run(PCBList &plist){
    std::cout<<"输入选择的算法:\n1.轮转法\t2.先来先服务\t3.短作业优先(抢占)\t4.静态优先权\n";
    int x;std::cin>>x;
    ScheduleAlgo* algo;
    switch (x){
    case 1:algo=new RoundRobin(plist); break;
    case 2:algo=new FirstServer(plist); break;
    case 3:algo=new ShortJob(plist); break;
    case 4:algo=new StaticPriority(plist); break;
    default:break;
    }
    while(!algo->isFinish()){
        algo->step();
        std::cout<<"###################################\n";
        std::cout<<algo->getCLOCK()<<'\n';
        printPCBlist(plist);
    }
    report(plist,algo->endTime());
    delete algo;
}

int main(){
    system("chcp 65001");
    PCBList plist(7);
    for(int i=0;i<plist.size();i++)
        plist[i]=new PCB(RAND_INT(1,20),RAND_INT(0,60),RAND_INT(10,40));
    
    std::cout<<PCBList_toString(plist);
    run(plist);
    for(auto &ptr:plist)delete ptr;
    return 0;
}