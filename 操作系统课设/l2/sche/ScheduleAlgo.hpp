#pragma once
#include "PCB.hpp"
#include <vector>
#include <map>
class ScheduleAlgo{
public:
    ScheduleAlgo(const PCBList& plist):plist(plist){CLOCK=0;}
    virtual std::string step()=0;
    inline bool isFinish(){return plist.empty();}
    inline int getCLOCK(){return CLOCK;}
    inline std::map<PCB*,int> endTime(){return _endTime;} 
protected:
    PCBList plist;
    int CLOCK;
    std::map<PCB*,int>_endTime;
};