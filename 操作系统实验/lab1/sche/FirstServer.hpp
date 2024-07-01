#pragma once
#include "ScheduleAlgo.hpp"
#include <queue>
#include <algorithm>
typedef std::queue<PCB*> Queue;

class FirstServer:public ScheduleAlgo{
public:
    FirstServer(const PCBList& plist):ScheduleAlgo(plist){}
    inline std::string step() override{
        for(auto pcb:plist){
            if(pcb->startTime()<=CLOCK && pcb->state()!=finish){
                if(pcb->state()==none)
                    q.push(pcb);
                pcb->set_state(ready);
            }
        }
        if(q.empty()){
            std::string msg=std::to_string(CLOCK)+" -1";
            CLOCK++;
            return msg;
        }
        auto pcb=q.front();
        if(pcb->state()==ready){
            for(auto _pcb:plist){
                if(pcb==_pcb)
                _pcb->set_state(running);
            }
        }
        std::string msg=std::to_string(CLOCK)+" "+std::to_string(pcb->pid());
        pcb->set_needTime(pcb->needTime()-1);
        if(pcb->needTime()==0){
            pcb->set_state(finish);
            _endTime[pcb]=CLOCK;
            q.pop();
            plist.erase(std::find(plist.begin(),plist.end(),pcb));
        }
        CLOCK++;
        return msg;
    }
private:
    typedef std::queue<PCB*> Queue;
    Queue q;
};