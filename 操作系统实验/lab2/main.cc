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

struct pcb{
    veci Max;
    veci Allocation;
};

void print_pcbs(const vector<pcb>&pcbs,const veci& Resource){
    int n=pcbs.size();
    int m=Resource.size();
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
#include "util.hpp"
int main(){
    srand(131);
    int n=RAND_INT(4,8);
    int m=RAND_INT(3,5);
    veci Resource(m);
    FILL_WITH_RAND_INT(Resource.begin(),Resource.end(),3,15);
    print(Resource);
    vector<pcb> pcbs(n);
    for(auto&pcb:pcbs){
        pcb.Allocation.resize(m);
        pcb.Max.resize(m);
        FILL_WITH_RAND_INT(pcb.Allocation.begin(),pcb.Allocation.end(),1,15);
        FILL_WITH_RAND_INT(pcb.Max.begin(),pcb.Max.end(),1,20);
    }
    print_pcbs(pcbs,Resource);

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
    
    return 0;
}