#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <set>
using namespace std;
struct state{
    int x,y;
    bool f;
};
bool operator<(const state& s1,const state& s2){
    if(s1.x!=s2.x)return s1.x<s2.x;
    if(s1.y!=s2.y)return s1.y<s2.y;
    if(s1.f!=s2.f)return s1.f<s2.f;
    return false;
}
bool operator==(const state& s1,const state& s2){
    return s1.x==s2.x && s1.y==s2.y && s1.f==s2.f;
}
    
const bool L = 1, R = 0;
struct op{
    int dx,dy;
};

state s,e;
vector<op>ops;
int n,c;
int m=0;
map<state,int>st_to_i;
map<int,state>i_to_st;
set<pair<int,int>>cnt_edge;
vector<int>g[(size_t)1e7];

bool check(int x,int y){
    return x>=0 && x<=n && y>=0 && y<=n;
}
void build(int u){
    auto[x,y,f]=i_to_st[u];
    for(auto[dx,dy]:ops){
        int p=f?-1:1;
        int nx=x+p*dx,ny=y+p*dy;
        if(!check(nx,ny)) continue;
        state temp={nx,ny,(bool)(f^true)};
        if( (nx>=ny || nx==0) && (n-nx >= n-ny || n-nx == 0)){
            if(st_to_i.count(temp)==0){
                int v=++m;
                st_to_i.insert({temp,v});
                i_to_st.insert({v,temp});
                cnt_edge.insert(make_pair(u,v));
                cnt_edge.insert(make_pair(v,u));
                g[u].push_back(v);
                g[v].push_back(u);
                build(v);
            }else{
                int v=st_to_i[temp];
                if(cnt_edge.count(make_pair(u,v))!=0)
                    continue;
                cnt_edge.insert(make_pair(u,v));
                cnt_edge.insert(make_pair(v,u));
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
    }
}

vector<int>pref;
vector<int>dis;
typedef pair<int,int> PII;
void dijkstra(){
    priority_queue<PII,vector<PII>,greater<PII>>pq;
    dis[0]=0;
    pq.emplace(dis[0],0);
    while(!pq.empty()){
        auto[d,u]=pq.top();pq.pop();
        if(dis[u]<d)continue;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i],w=1;
            if(dis[v]>dis[u]+w){
                pref[v]=u;
                dis[v]=dis[u]+w;
                pq.emplace(dis[v],v);
            }
        }
    }
}
void printPath(){
    int t=st_to_i[e];
    stack<int>stc;
    while(t!=0){
        stc.push(t);
        t=pref[t];
    }
    stc.push(0);
    vector<state>ls;
    while(!stc.empty()){
        ls.push_back(i_to_st[stc.top()]);
        stc.pop();
    }
    string s[2]={"回来","去对岸"};
    for(int i=1;i<ls.size();i++){
        if(i&1){
            cout<<ls[i-1].x<<"传教士 "<<ls[i-1].y<<"野人--->";
            cout<<ls[i-1].x-ls[i].x<<"个传教士和"<<ls[i-1].y-ls[i].y<<"个野人"<<s[i&1]<<"--->";
            cout<<ls[i].x<<"传教士 "<<ls[i].y<<"野人\n";
        }else{
            cout<<ls[i-1].x<<"传教士 "<<ls[i-1].y<<"野人--->";
            cout<<ls[i].x-ls[i-1].x<<"个传教士和"<<ls[i].y-ls[i-1].y<<"个野人"<<s[i&1]<<"--->";
            cout<<ls[i].x<<"传教士 "<<ls[i].y<<"野人\n";
        }
    }
}

int main(){
#ifndef __linux__
    system("chcp 65001");
#endif
    cin>>n>>c;
    if(c>=2*n){
        cout<<"共需要渡河"<<1<<"次\n";
        return 0;
    }else if(c>=n && c<2*n){
        cout<<"共需要渡河"<<5<<"次\n";
        return 0;
    }
    s={n,n,L};
    e={0,0,R};
    st_to_i.insert({s,0}),i_to_st.insert({0,s});
    for(int i=0;i<=c;i++){
        for(int j=0;j<=c;j++){
            if(i==0 && j==0) continue;
            if(i+j>c) continue;
            if(i>=j || i==0){
                ops.push_back({i,j});
                ops.push_back({i,j});
            }
        }
    }
    build(0);
    if(st_to_i.count(e)==0){
        cout<<-1<<'\n';
        return 0;
    }
    pref.resize(m+1);
    dis.resize(m+1,1e9);
    dijkstra();
    printPath();
    cout<<"共需要渡河"<<dis[st_to_i[e]]<<"次\n";
    return 0;
}