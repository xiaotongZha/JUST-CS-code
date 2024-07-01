#include <iostream>
#include <cstring>
#include <map>
#include <set>
#include <functional>
using namespace std;
typedef unsigned char Byte;
#define MEM_SIZE 1024
Byte* mem;
void mem_watch(){
    for(int i=0;i<MEM_SIZE;i++){
        printf("%d:%d%c",i,mem[i],"\t\n"[(i+1)%16==0]);
    }
}
map<Byte,Byte*>mp;
void mem_FF(Byte x,int len){
    bool ok=0;
    for(int i=0;i<MEM_SIZE && !ok;i++){
        if(mem[i]==0){
            int s=i;
            for(;i<MEM_SIZE && mem[i]==0;i++);
            if(i-s>=len){
                memset(mem+s,x,len);
                mp.insert({x,mem+s});
                ok=1;
            }
        }
    }    
    if(!ok) cout<<"没有足够大的空间了\n";
}
int pos=0;
void mem_NF(Byte x,int len){ 
    bool ok=0;
    int tmp=pos;
    for(;pos<MEM_SIZE;pos++){
        if(mem[pos]==0){
            int s=pos;
            for(;pos<MEM_SIZE && mem[pos]==0;pos++)
                if(pos-s==len){
                    memset(mem+s,x,len);
                    mp.insert({x,mem+s});
                    ok=1;
                    break;
                }
        }
        if(ok) return;
    }  
    pos=0;
    for(;pos<tmp;pos++){
        if(mem[pos]==0){
            int s=pos;
            for(;pos<tmp && mem[pos]==0;pos++);
            if(pos-s>=len){
                memset(mem+s,x,len);
                mp.insert({x,mem+s});
                ok=1;
            }
        }
    }  
    if(!ok) cout<<"没有足够大的空间了\n";
}
void mem_BF(Byte x,int len){
    set<pair<int,Byte*>> st;
    for(int i=0;i<MEM_SIZE;i++){
        if(mem[i]==0){
            int s=i;
            for(;i<MEM_SIZE && mem[i]==0;i++);
            if(i-s>=len)
                st.insert({i-s,mem+s});                
        }
    }
    if(st.empty()){
        cout<<"没有足够大的空间了\n";
        return;
    }
    Byte* ptr=st.begin()->second;
    memset(ptr,x,len);
    mp.insert({x,ptr});
}
void mem_WF(Byte x,int len){
    set<pair<int,Byte*>> st;
    for(int i=0;i<MEM_SIZE;i++){
        if(mem[i]==0){
            int s=i;
            for(;i<MEM_SIZE && mem[i]==0;i++);
            if(i-s>=len)
                st.insert({i-s,mem+s});                
        }
    }
    if(st.empty()){
        cout<<"没有足够大的空间了\n";
        return;
    }
    Byte* ptr=st.rbegin()->second;
    memset(ptr,x,len);
    mp.insert({x,ptr});
}
void mem_release(Byte x){
    Byte* ptr=mp[x];
    int s=ptr-mem;
    int e=s;
    for(;e<MEM_SIZE && mem[e]==x;e++);
    memset(ptr,0,e-s);
}
int main(){
    system("chcp 65001");
    mem=(Byte*)malloc(MEM_SIZE);
    memset(mem,0,MEM_SIZE);
    void (*mf[4])(Byte,int) ={mem_FF,mem_NF,mem_BF,mem_WF};
    printf("请选择分配算法\n0.首次适应\n1.循环适应\n2.最好适应\n3.最坏适应\n");
    int ii;cin>>ii;
    while(1){
        string cmd;cin>>cmd;
        if(cmd=="watch"){
            mem_watch();
        }else if(cmd=="alloc"){
            Byte x;int len;
            cin>>x>>len;
            x-='0';
            mf[ii](x,len);
            printf("alloc ok\n");
        }else if(cmd=="release"){
            Byte x;cin>>x;
            x-='0';
            mem_release(x);
        }
    }
    
    return 0;
}