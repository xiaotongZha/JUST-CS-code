#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <functional>

using namespace std;

#define RAND_INT(l,r) ((rand()%(r-l+1))+l)
#define FILL_WITH_RAND_INT(it1,it2,l,r) \
    for(auto it=it1;it!=it2;it++)\
        *it=RAND_INT(l,r);

typedef vector<int> veci;
veci operator+(const veci& v1,const veci& v2){
    if(v1.size()!=v2.size())
        throw std::invalid_argument("vectors length is not equal");
    veci v3(v1.size());
    for(int i=0;i<v1.size();i++)
        v3[i]=v1[i]+v2[i];
    return v3;
}
veci operator-(const veci& v1,const veci& v2){
    if(v1.size()!=v2.size())
        throw std::invalid_argument("vectors length is not equal");
    veci v3(v1.size());
    for(int i=0;i<v1.size();i++)
        v3[i]=v1[i]-v2[i];
    return v3;
}
bool operator<=(const veci& v1,const veci& v2){
    if(v1.size()!=v2.size())
        throw std::invalid_argument("vectors length is not equal");
    for(int i=0;i<v1.size();i++){
        if(v1[i]>v2[i])
            return false;
    }
    return true;    
}
bool operator<(const veci& v1,const veci& v2){
    if(v1.size()!=v2.size())
        throw std::invalid_argument("vectors length is not equal");
    for(int i=0;i<v1.size();i++){
        if(v1[i]>=v2[i])
            return false;
    }
    return true;    
}

struct PCB{
    veci Max;
    veci Allocation;
};
bool operator<(const PCB& pcb1,const PCB& pcb2){
    return pcb1.Max-pcb1.Allocation < pcb2.Max-pcb2.Allocation;
}
int n,m;
veci Resource;
vector<PCB> pcbs;
void print_pcbs(const vector<PCB>&pcbs,const veci& Resource){
    cout<<"Resource:";
    for(int i=0;i<m;i++)
        cout<<Resource[i]<<" \n"[i+1==Resource.size()];
    for(int i=0;i<n;i++){
        cout<<"id:"<<i<<'\t';
        cout<<"Max:";
        for(auto x:pcbs[i].Max)
            cout<<x<<' ';
        cout<<'\t';
        cout<<"Allocation:";
        for(auto x:pcbs[i].Allocation)
            cout<<x<<' ';
        cout<<'\n';
    }   
}
void print_all_safe_seq(){
    vector<veci>res;
    function<void(int,veci&,veci&,veci&)>dfs=[&](int u,veci& tmp,veci& Work,veci& vis){
        if(tmp.size()==n){
            res.push_back(tmp);
            return;
        }
        for(int i=0;i<n;i++){
            if(vis[i])continue;
            if(pcbs[i].Max <= Work+pcbs[i].Allocation){
                Work=Work+pcbs[i].Allocation;
                tmp.push_back(i);
                vis[i]=1;
                dfs(i,tmp,Work,vis);
                vis[i]=0;
                tmp.pop_back();
                Work=Work-pcbs[i].Allocation;
            }
        }
    };
    
    for(int i=0;i<n;i++){
        if(pcbs[i].Max <= Resource+pcbs[i].Allocation){
            veci vis(n);
            veci Work=Resource+pcbs[i].Allocation;
            veci tmp;
            tmp.push_back(i);
            vis[i]=1;
            dfs(i,tmp,Work,vis);
        }
    }
    cout<<"safe sequnece:\n";
    for(auto &v:res){
        for(auto &x:v)
            cout<<x<<' ';
        cout<<'\n';
    }
}
veci find_safe_seq(){
    veci res;
    bool ok=0;
    function<void(int,veci&,veci&,veci&)>dfs=[&](int u,veci& tmp,veci& Work,veci& vis){
        if(ok)return;
        if(tmp.size()==n){
            res=tmp;
            ok=1;
            return;
        }
        for(int i=0;i<n;i++){
            if(vis[i])continue;
            if(pcbs[i].Max <= Work+pcbs[i].Allocation){
                Work=Work+pcbs[i].Allocation;
                tmp.push_back(i);
                vis[i]=1;
                dfs(i,tmp,Work,vis);
                vis[i]=0;
                tmp.pop_back();
                Work=Work-pcbs[i].Allocation;
            }
        }
    };
    for(int i=0;i<n;i++){
        if(ok)break;
        if(pcbs[i].Max <= Resource+pcbs[i].Allocation){
            veci vis(n);
            veci Work=Resource+pcbs[i].Allocation;
            veci tmp;
            tmp.push_back(i);
            vis[i]=1;
            dfs(i,tmp,Work,vis);
        }
    }
    return res;
}
void load1(){
    int sr;cin>>sr;
    srand(sr);
    n=RAND_INT(4,8);//进程数
    m=RAND_INT(3,5);//资源种类数
    Resource.resize(m);
    FILL_WITH_RAND_INT(Resource.begin(),Resource.end(),3,15);
    pcbs.resize(n);
    for(auto&pcb:pcbs){
        pcb.Allocation.resize(m);
        pcb.Max.resize(m);
        FILL_WITH_RAND_INT(pcb.Allocation.begin(),pcb.Allocation.end(),1,15);
        FILL_WITH_RAND_INT(pcb.Max.begin(),pcb.Max.end(),1,20);
    }
}
#include <fstream>
void load2(){
    ifstream ifs("input.txt");
    ifs>>n>>m;
    Resource.resize(m);
    pcbs.resize(n);
    for(int i=0;i<m;i++)
        ifs>>Resource[i];
    for(auto&pcb:pcbs){
        pcb.Allocation.resize(m);
        pcb.Max.resize(m);
        for(int i=0;i<m;i++)
            ifs>>pcb.Allocation[i];
        for(int i=0;i<m;i++)
            ifs>>pcb.Max[i];
    }
    ifs.close();
}
#include "util.hpp"
int main(){
    load2();
    sort(pcbs.begin(),pcbs.end());
    print_pcbs(pcbs,Resource);
    veci Requset(m);
    FILL_WITH_RAND_INT(Requset.begin(),Requset.end(),1,5);
    int idx=RAND_INT(0,n-1);
    cout<<"process"<<idx<<" ";
    print(Requset);
    pcbs[idx].Max=pcbs[idx].Max+Requset;
    print_pcbs(pcbs,Resource);
    veci res=find_safe_seq();
    print(res);
    return 0;
}