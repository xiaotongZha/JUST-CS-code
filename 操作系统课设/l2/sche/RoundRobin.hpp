#pragma once
#include "ScheduleAlgo.hpp"
#include <queue>
#include <algorithm>

class RoundRobin:public ScheduleAlgo{
public:
    RoundRobin(const PCBList& plist):ScheduleAlgo(plist),now_pcb(nullptr){}
    inline std::string step() override{
        for(auto pcb:plist){
            if(pcb->startTime()<=CLOCK && pcb->state()!=finish){
                if(pcb->state()==none)
                   q.push(pcb);
                pcb->set_state(ready);
            }
        }
        if(now_pcb!=nullptr && now_pcb->state()!=finish){
            q.push(now_pcb);
        }
        if(q.empty()){
            std::string msg=std::to_string(CLOCK)+" -1";
            CLOCK++;
            return msg;
        }
        auto pcb=q.front();
        q.pop();
        pcb->set_state(running);
        std::string msg=std::to_string(CLOCK)+" "+std::to_string(pcb->pid());
        pcb->set_needTime(pcb->needTime()-1);
        if(pcb->needTime()==0){
            pcb->set_state(finish);
            _endTime[pcb]=CLOCK;
            plist.erase(std::find(plist.begin(),plist.end(),pcb));
        }
        now_pcb=pcb;
        CLOCK++;
        return msg;
    }
private:
    typedef std::queue<PCB*> Queue;
    Queue q;
    PCB *now_pcb;
};