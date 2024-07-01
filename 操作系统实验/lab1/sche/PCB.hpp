#pragma once
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
enum{
    ready=0,running=1,finish=2,none=3
};
class PCB{
public:
    PCB(int priority,int startTime,int serveTime):_pid(PCB::cnt++),_state(none),_priority(priority),_startTime(startTime),_serveTime(serveTime),_needTime(serveTime){}

    inline int pid()const{return _pid;}
    inline int priority()const{return _priority;}
    inline void set_priority(int priority){_priority=priority;}
    inline int state()const{return _state;}
    inline void set_state(int state){_state=state;}
    inline const char*stateMsg()const{return _stateMsg[_state];}
    inline int startTime()const{return _startTime;}
    inline int serveTime()const{return _serveTime;}
    inline int needTime()const{return _needTime;}
    inline void set_needTime(int needTime){_needTime=needTime;}
    bool operator==(const PCB&oth){return _pid==oth.pid();}
    bool operator<(const PCB&oth){return _pid<oth.pid();}

private:
    int _pid;
    int _priority;
    int _state;
    int _startTime;
    int _serveTime;
    int _needTime;
    const char* _stateMsg[4]={"ready","running","finish","none"};
public:
    static int cnt;
};

int PCB::cnt=0;

typedef std::vector<PCB*> PCBList;

void printPCBlist(const PCBList&plist){
    printf("pid\tprior\tstate\tstart\tserve\tleave\n");
    for(auto&pcb:plist)
        printf("%d\t%d\t%s\t%d\t%d\t%d\n",pcb->pid(),pcb->priority(),pcb->stateMsg(),pcb->startTime(),pcb->serveTime(),pcb->needTime());
}
std::string PCBList_toString(const PCBList&pList){
    char buf[256];
    std::string res;
    for(auto&pcb:pList){
        memset(buf,0,sizeof(buf));
        sprintf(buf,"%d\t%d\t%s\t%d\t%d\n",pcb->pid(),pcb->priority(),pcb->stateMsg(),pcb->startTime(),pcb->serveTime());
        res.append(buf);
    }
    return res;
}