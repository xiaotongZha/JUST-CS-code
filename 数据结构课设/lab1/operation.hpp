#include "flight.hpp"
#include <fstream>
#include <sstream>
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
void read_data(FlightFind &fs,const string &filename){
    ifstream ifs;
    if(filename=="random")
        ifs.open("info.txt");
    else
        ifs.open(filename);
    if(!ifs.is_open())
        throw "fail to open\n";
    int id;
    string startPort,endPort;
    string startTime_YMD,startTime_HMS,endTime_YMD,endTime_HMS;
    int type;  
    double price; 
    while(!ifs.eof()){
        ifs>>id>>startPort>>endPort>>startTime_YMD>>startTime_HMS>>endTime_YMD>>endTime_HMS>>type>>price;
        //cout<<startTime_YMD<<' '<<startTime_HMS<<'\n';
        string startTime=startTime_YMD+" "+startTime_HMS;
        string endTime=endTime_YMD+" "+endTime_HMS;
        Flight fly(id,startPort,endPort,Date(startTime),Date(endTime),type,price);
        fs.insert(fly);
    }
}

vector<Flight> single_find(FlightFind& fs,int op,const string&cond){
    vector<Flight> res;
    switch(op){
        case 1:
            res.push_back(fs.find_by_id(atoi(cond.c_str())));
            break;
        case 2:
            res=fs.find_by_startPort(cond);
            break;
        case 3:
            res=fs.find_by_endPort(cond);
            break;
        case 4:
            res=fs.find_by_startTime(Date(cond));
            break;
        case 5:
            res=fs.find_by_endTime(Date(cond));
            break;
        case 6:
            res=fs.find_by_type(atoi(cond.c_str()));
            break;
        case 7:
            res=fs.find_by_price(atof(cond.c_str()));
            break;
        default:
            break;
    }
    return res;
}
vector<Flight> single_range_find(FlightFind & fs,int op,const string&cond1,const string&cond2){
    vector<Flight> res;
    switch(op){
        case 1:
            res=fs.find_by_startTime(Date(cond1),Date(cond2));
            break;
        case 2:
            res=fs.find_by_endTime(Date(cond1),Date(cond2));
            break;
        case 3:
            res=fs.find_by_price(atof(cond1.c_str()),atof(cond2.c_str()));
            break;
    }
    return res;
}
vector<Flight> muti_find(FlightFind&fs,string&ops,const vector<string>&conds){
    int op=ops[0]-'0';
    vector<Flight>res;
    if(op>=0 && op<=6)
        res=single_find(fs,op+1,conds[0]);
    else if(op==7 || op==8){
        int pos1=conds[0].find_first_of(' ');
        int space=conds[0].find(' ',pos1+1);
        string cond1=conds[0].substr(0,space);
        string cond2=conds[0].substr(space+1,conds[0].size());
        cout<<cond1<<' '<<cond2<<'\n';
        res=single_range_find(fs,op-6,cond1,cond2);
    }else if(op==9){

        res=single_range_find(fs,op-6,
            conds[0].substr(0,conds[0].find_first_of(' ')),
            conds[0].substr(conds[0].find_first_of(' ')+1,conds[0].size()));
    }
    vector<Flight>ans;
    for(auto &em:res){
        bool ok=1;
        for(int i=1;i<ops.size();i++){
            switch (ops[i]-'0'){
            case 1:
                if(em.get_startPort()!=conds[i])
                    ok=0;
                break;
            case 2:
                if(em.get_endPort()!=conds[i])
                    ok=0;
                break;
            case 3:
                if(em.get_startTime()!=Date(conds[i]))
                    ok=0;
                break;
            case 4:
                if(em.get_endTime()!=Date(conds[i]))
                    ok=0;
                break;
            case 5:
                if(em.get_type()!=atoi(conds[i].c_str()))
                    ok=0;
                break;
            case 6:
                if(em.get_price()!=atof(conds[i].c_str()))
                    ok=0;
                break;
            case 7:
            {   
                int pos1=conds[i].find_first_of(' ');
                int space=conds[i].find(' ',pos1+1);
                string cond1=conds[i].substr(0,space);
                string cond2=conds[i].substr(space+1,conds[i].size());
                if(em.get_startTime() < Date(cond1)
                || em.get_startTime() > Date(cond2))
                    ok=0;
                break;
            }
            case 8:
            {
                int pos1=conds[i].find_first_of(' ');
                int space=conds[i].find(' ',pos1+1);
                string cond1=conds[i].substr(0,space);
                string cond2=conds[i].substr(space+1,conds[i].size());
                if(em.get_endTime() < Date(cond1)
                || em.get_endTime() > Date(cond2))
                    ok=0;   
                break;
            }
            case 9:
            {
                string cond1=conds[i].substr(0,conds[i].find_first_of(' '));
                string cond2=conds[i].substr(conds[i].find_first_of(' ')+1,conds[i].size());
                if(em.get_price() < atof(cond1.c_str())
                || em.get_price() > atof(cond2.c_str()))
                    ok=0;  
                break; 
            }
            default:
                break;
            }
        }
        if(ok)
            ans.push_back(em);
    }
    return ans; 
}
