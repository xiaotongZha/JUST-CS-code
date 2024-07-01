#include "flight.hpp"
#include <iostream>
#include <fstream>
#include "operation.hpp"
#include "ui.hpp"
using namespace std;

int main() {
    UI ui("ui.txt");
    ui.printPage(0);
    FlightFind ffi;
    while(1){
        string cmd;cin>>cmd;
        if(cmd=="quit")
            break;
        if(cmd=="1"){
            ui.printPage(1);
            cout<<"请输入文件名:\n";
            string filename;cin>>filename;
            if(filename=="back"){
                ui.printPage(0);
            }else{
                read_data(ffi,filename);
                cout<<"数据导入成功!2秒后返回\n";
                SLEEP(2);
                ui.printPage(0);
            }
        }
        else if(cmd=="2"){
            ui.printPage(2);
            cout<<"请输入查询指令:\n";
            int op;string cond;
            cin>>op;
            if(op==4 || op==5){
                cin>>cond;
                string tmp;cin>>tmp;
                cond+=" "+tmp;
            }else{
                cin>>cond;
            }
            auto res=single_find(ffi,op,cond);
            for(auto&em:res)
                cout<<em<<'\n';
            cout<<"查询成功!输入back返回\n";
            string tmp;
            while(1){
                cin>>tmp;
                if(tmp=="back"){
                    ui.printPage(0);
                    break;
                }
            }
        }
        else if(cmd=="3"){
            ui.printPage(3);
            cout<<"请输入查询指令:\n";
            int op;string cond1,cond2;
            cin>>op;
            if(op==1 || op==2){
                string tmp;
                cin>>cond1>>tmp;
                cond1+=" "+tmp;
                cin>>cond2>>tmp;
                cond2+=" "+tmp;
            }else{
                cin>>cond1>>cond2;   
            }
            auto res=single_range_find(ffi,op,cond1,cond2);
            for(auto&em:res)
                cout<<em<<'\n';
            cout<<"查询成功!输入back返回\n";
            string tmp;
            while(1){
                cin>>tmp;
                if(tmp=="back"){
                    ui.printPage(0);
                    break;
                }
            }
        }else if(cmd=="4"){
            ui.printPage(4);
            cout<<"请输入查询指令:\n";
            string ops;cin>>ops;
            vector<string>conds(ops.size());
            for(int i=0;i<conds.size();i++){
                if(ops[i]=='7' || ops[i]=='8'){
                    string cond1,cond2;
                    cin>>cond1>>cond2;
                    conds[i]=cond1+" "+cond2;
                    cin>>cond1>>cond2;
                    conds[i]+=" "+cond1+" "+cond2;
                }
                else if(ops[i]=='9'){
                    string cond1,cond2;
                    cin>>cond1>>cond2;
                    conds[i]=cond1+" "+cond2;
                }
                else if(ops[i]=='3' ||ops[i]=='4'){ 
                    string cond1,cond2;
                    cin>>cond1>>cond2;
                    conds[i]=cond1+" "+cond2;    
                }
                else{
                    cin>>conds[i];
                }
            }
            auto res=muti_find(ffi,ops,conds);
            for(auto &em:res)
                cout<<em<<'\n';
            cout<<"查询成功!输入back返回\n";
            string tmp;
            while(1){
                cin>>tmp;
                if(tmp=="back"){
                    ui.printPage(0);
                    break;
                }
            }
        }
    }
    return 0;
}
