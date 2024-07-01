#pragma once
#include "ScheduleAlgo.hpp"
#include <queue>
#include <algorithm>

class StaticPriority:public ScheduleAlgo{
public:
    StaticPriority(const PCBList& plist):ScheduleAlgo(plist){}
    inline std::string step() override{
        for(auto pcb:plist){
            if(pcb->startTime()<=CLOCK && pcb->state()!=finish){
                if(pcb->state()==none)
                    mh.emplace(pcb->needTime(),pcb);
                pcb->set_state(ready);
            }
        }
        if(mh.empty()){
            std::string msg=std::to_string(CLOCK)+" -1";
            CLOCK++;
            return msg;
        }
        auto pcb=mh.top().second;
        mh.pop();
        pcb->set_state(running);

        std::string msg=std::to_string(CLOCK)+" "+std::to_string(pcb->pid());
        pcb->set_needTime(pcb->needTime()-1);
        if(pcb->needTime()==0){
            pcb->set_state(finish);
            _endTime[pcb]=CLOCK;
            plist.erase(std::find(plist.begin(),plist.end(),pcb));
        }else{
            mh.emplace(pcb->priority(),pcb);
        }
        CLOCK++;
        return msg;
    }
private:
    typedef std::priority_queue<std::pair<int,PCB*>> MaxHeap;
    MaxHeap mh;
};