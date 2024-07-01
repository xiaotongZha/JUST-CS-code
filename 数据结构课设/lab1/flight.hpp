#ifndef FLIGHT
#define FLIGHT

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include "Date.hpp"
using namespace std;

#define MAX_TYPE 20
class Flight {
private:
    int id;
    string startPort;
    string endPort;
    Date startTime;
    Date endTime;
    int type;  
    double price;  
public:
    Flight() : id(-1), price(-1), type(-1) {}

    Flight(int id, std::string startPort, std::string endPort, Date startTime, Date endTime, int type, double price) :
        id(id), startPort(startPort), endPort(endPort), startTime(startTime), endTime(endTime), type(type), price(price) {}
    int get_id() const { return id; }
    void set_id(int newId) { id = newId; }

    const string& get_startPort() const { return startPort; }
    void set_startPort(const string& newStartPort) { startPort = newStartPort; }

    const string& get_endPort() const { return endPort; }
    void set_endPort(const string& newEndPort) { endPort = newEndPort; }

    const Date& get_startTime() const { return startTime; }
    void set_startTime(const Date& newStartTime) { startTime = newStartTime; }

    const Date& get_endTime() const { return endTime; }
    void set_endTime(const Date& newEndTime) { endTime = newEndTime; }

    int get_type() const { return type; }
    void set_type(int newType) { type = newType; }

    double get_price() const { return price; }
    void set_price(double newPrice) { price = newPrice; }

    friend ostream& operator<<(ostream& os, const Flight& flight);
};
ostream& operator<<(ostream& os, const Flight& flight) {
    os << "ID: " << flight.get_id() << "\n"
       << "Start Port: " << flight.get_startPort() << "\n"
       << "End Port: " << flight.get_endPort() << "\n"
       << "Start Time: " << flight.get_startTime() << "\n"
       << "End Time: " << flight.get_endTime() << "\n"
       << "Type: " << flight.get_type() << "\n"
       << "Price: " << flight.get_price() << "\n";
    os<<'\n';
    return os;
}

class FlightFind{
public:
    typedef std::unordered_map<int, Flight>::const_iterator iterator;
    FlightFind(){}
    FlightFind(const vector<Flight>& flys){
        for(const auto &em:flys)
           __insert(em);
        length=flys.size();
    }
    void insert(const Flight &fly){
        __insert(fly);
        length++;
    }
    void erase_by_id(int id){
        auto iter=id_sort.find(id);
        if(iter==id_sort.end())
            return;
        int _id=iter->second.get_id();
        id_sort.erase(iter);
        __erase(_id,startPort_sort);
        __erase(_id,endPort_sort);
        __erase(_id,startTime_sort);
        __erase(_id,endTime_sort);
        __erase(_id,price_sort);
        
    }
    iterator begin()const{
        return id_sort.begin();
    }
    iterator end()const{
        return id_sort.end();
    }
    size_t size(){
        return length;
    }

    Flight find_by_id(int _id){
        return id_sort[_id];
    }
    vector<Flight> find_by_type(int _type){
        if(_type>=MAX_TYPE)
            return {};
        else
            return type_sort[_type];
    }
    vector<Flight> find_by_startTime(const Date& _startTime){
        vector<Flight> res;
        auto range=startTime_sort.equal_range(_startTime);
        for(auto it=range.first;it!=range.second;it++)
            res.push_back(it->second);
        return res;
    }
    vector<Flight> find_by_endTime(const Date& _endTime){
        vector<Flight> res;
        auto range=endTime_sort.equal_range(_endTime);
        for(auto it=range.first;it!=range.second;it++)
            res.push_back(it->second);
        return res;
    }
    vector<Flight> find_by_startPort(const string& _startPort){
        vector<Flight> res;
        auto range=startPort_sort.equal_range(_startPort);
        for(auto it=range.first;it!=range.second;it++)
            res.push_back(it->second);
        return res;
    }
    vector<Flight> find_by_endPort(const string& _endPort){
        vector<Flight> res;
        auto range=startPort_sort.equal_range(_endPort);
        for(auto it=range.first;it!=range.second;it++)
            res.push_back(it->second);
        return res;
    }
    vector<Flight> find_by_price(double _price){
        vector<Flight> res;
        auto range=price_sort.equal_range(_price);
        for(auto it=range.first;it!=range.second;it++)
            res.push_back(it->second);
        return res;
    }

    //范围查找
    vector<Flight> find_by_startTime(const Date& time1,const Date& time2){
        vector<Flight> res;
        if(time1>time2)
            return res;
        auto iter1=startTime_sort.lower_bound(time1);
        auto iter2=startTime_sort.upper_bound(time2);
        for(auto it=iter1;it!=iter2;it++)
            res.push_back(it->second);
        return res;
    }
    vector<Flight> find_by_endTime(const Date& time1,const Date& time2){
        vector<Flight> res;
        if(time1>time2)
            return res;
        auto iter1=endTime_sort.lower_bound(time1);
        auto iter2=endTime_sort.upper_bound(time2);
        for(auto it=iter1;it!=iter2;it++)
            res.push_back(it->second);
        return res;
    }
    vector<Flight> find_by_price(double price1,double price2){
        vector<Flight> res;
        if(price1>price2)
            return res;
        auto iter1=price_sort.lower_bound(price1);
        auto iter2=price_sort.upper_bound(price2);
        for(auto it=iter1;it!=iter2;it++)
            res.push_back(it->second);
        return res;
    }
private:
    size_t length=0;

    unordered_map<int,Flight> id_sort;
    multimap<Date,Flight> startTime_sort;
    multimap<Date,Flight> endTime_sort;
    multimap<double,Flight> price_sort;
    multimap<string,Flight> startPort_sort;
    multimap<string,Flight> endPort_sort;
    array<vector<Flight>,MAX_TYPE> type_sort;

    void __insert(const Flight &fly){
        id_sort.insert({fly.get_id(),fly});
        startPort_sort.insert({fly.get_startPort(),fly});
        endPort_sort.insert({fly.get_endPort(),fly});
        startTime_sort.insert({fly.get_startTime(),fly});
        endTime_sort.insert({fly.get_endTime(),fly});
        type_sort[fly.get_type()].push_back(fly);
        price_sort.insert({fly.get_price(),fly});
    }
    template<class Container>
    void __erase(int _id,Container& c){
        for(auto it=c.begin();it!=c.end();it++)
            if(it->second.get_id()==_id)
                c.erase(it);
    }

};
#endif