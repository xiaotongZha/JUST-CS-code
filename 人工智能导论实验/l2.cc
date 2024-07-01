#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <queue>
using namespace std;
int init_st[3][3]={
    {1,2,3},
    {4,0,6},
    {7,5,8}
};
int fin_st[3][3]={
    {1,2,3},
    {4,5,6},
    {7,8,0}
};

class state{
public:
    state(){}
    state(int data[3][3]){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                this->data[i][j]=data[i][j];
    }
    state(const state&st){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                this->at(i,j)=st.at(i,j);
    }

    vector<state> nextStates()const{
        vector<state>res;
        auto vaild=[](int x,int y){
            return x>=0 && x<3 && y>=0 && y<3; 
        };
        auto[nx,ny]=this->findCeil(0);
        int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
        for(int i=0;i<4;i++){
            if(vaild(nx+dx[i],ny+dy[i])){
                state st(*this);
                swap(st.at(nx,ny),st.at(nx+dx[i],ny+dy[i]));
                res.push_back(st);
            }
        }
        return res;
    }
    vector<state> optNextStates()const{
        auto res=nextStates();
        sort(res.begin(),res.end(),[](const state&s1,const state&s2){
            return s1.heurFunc()<s2.heurFunc();
        });
        return res;
    }

    int& at(int x,int y){
        return this->data[x][y];
    }
    int at(int x,int y)const{
        return this->data[x][y];
    }
    state& operator=(const state&st){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                this->at(i,j)=st.at(i,j);
        return *this;
    }
    bool operator<(const state& st)const{
        return this->getId()<st.getId();
    }
    bool operator==(const state& st)const{
        return this->getId()==st.getId();
    }
    pair<int,int> findCeil(int x)const{
        if(x<0 || x>8) 
            return {-1,-1};
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(this->at(i,j)==x)
                    return {i,j};
        return {-1,-1};
    }
    void showState()const{
        printf("%d|%d|%d\n",this->at(0,0),this->at(0,1),this->at(0,2));
        printf("%d|%d|%d\n",this->at(1,0),this->at(1,1),this->at(1,2));
        printf("%d|%d|%d\n",this->at(2,0),this->at(2,1),this->at(2,2));
    }
    int heurFunc()const{
        int res=0;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(fin_st[i][j]==0)
                    continue;
                auto[ni,nj]=this->findCeil(fin_st[i][j]);
                res+=abs(ni-i)+abs(nj-j);
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(init_st[i][j]==0)
                    continue;
                auto[ni,nj]=this->findCeil(init_st[i][j]);
                res+=abs(ni-i)+abs(nj-j);
            }
        }
        return res;
    }
    int getId()const{
        int res=0;
        int cnt=1;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                res+=this->at(i,j)*cnt;
                cnt*=10;
            }
        }
        return res;
    }
    string get_op(const state& nextState){
        auto[cur_x,cur_y]=this->findCeil(0);
        auto[next_x,next_y]=nextState.findCeil(0);
        if(cur_x==next_x){
            if(cur_y<next_y)
                return "left";
            else
                return "right";
        }else{
            if(cur_x<next_x)
                return "up";
            else
                return "down";
        }
    }
    bool is_odd(){
        int arr[9];
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                arr[i*3+j]=this->at(i,j); 
        int cnt=0;
        for(int i=0;i<9;i++){
            for(int j=i-1;j>=0;j--){
                if(arr[i]==0||arr[j]==0)
                    continue;
                cnt+=arr[j]>arr[i];
            }
        }
        return cnt&1;  
    }
private:
    int data[3][3];
};
bool operator==(const pair<state,pair<int,string>>& s1,const pair<state,pair<int,string>>& s2){
    return s1.first==s2.first;
}
int main(){
#ifndef __linux__
    system("chcp 65001");
#endif
    printf("输入3*3个数字:\n");
    for(int i=0;i<9;i++) cin>>init_st[i/3][i%3];
    state firstState(init_st);
    state finalState(fin_st);
    if(firstState.is_odd()^finalState.is_odd()){
        printf("No Answer\n");
        return 0;
    }
    vector<pair<state,pair<int,string>>>open;
    map<state,int>close;
    
    open.push_back({firstState,{0,""}});
    while(!open.empty()){
        auto min_iter=min_element(open.begin(),open.end(),[](const pair<state,pair<int,string>>& s1,const pair<state,pair<int,string>>& s2){
            return s1.first.heurFunc()<s2.first.heurFunc();
        });
        auto[curState,info]=*min_iter;
        auto[step,curOp]=info;
        open.erase(min_iter);
        printf("------------------\nstep:%d\noperator:%s\n",step,curOp.c_str());
        curState.showState();
        printf("------------------\n");
        if(curState==finalState){
            printf("%d step to get answer\n",step);
            break;
        }
        for(const auto &nextState:curState.nextStates()){
            auto iter_close=close.find(nextState);
            auto iter_open=find(open.begin(),open.end(),make_pair(curState,make_pair(step,"")));
            if(iter_close==close.end() && iter_open==open.end()){
                open.push_back({nextState,{step+1,curState.get_op(nextState)}});
            }else if(iter_open!=open.end() && iter_open->second.first > step+1){
                iter_open->second.first=step+1;
                iter_open->second.second=curState.get_op(nextState);
            }else if(iter_close!=close.end() && iter_close->second > step+1){
                open.push_back({nextState,{step+1,curState.get_op(nextState)}});
                close.erase(iter_close);
            }
        }
        close.insert({curState,step});
    }
    
    return 0;
}