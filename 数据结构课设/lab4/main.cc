#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;
typedef pair<int,int> PII;
#define INF 0x3f3f3f3f

int n=10;
struct edge
{
    int to,w;
    edge(){}
    edge(int to,int w):to(to),w(w){}
};

vector<vector<edge>>g;
unordered_map<int,string>names;
vector<int> dijkstra(int s){
    vector<int>dis(n+1,INF);
    vector<bool>vis(n+1,0);
    priority_queue<PII,vector<PII>,greater<PII>>pq;
    pq.emplace(0,s);
    dis[s]=0;
    vis[s]=1;
    while(!pq.empty()){
        int u=pq.top().second,d=pq.top().first;pq.pop();
        vis[u]=1;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i].to,w=g[u][i].w;
            if(!vis[v] && dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                pq.emplace(dis[v],v);
            }
        }   
    }
    return dis;
}
vector<vector<int>> floyd(){
    vector<vector<int>>f(n+1,vector<int>(n+1));
    for(int u=1;u<=n;u++){
        for(auto &e:g[u])
            f[u][e.to]=e.w;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(f[i][j]>f[i][k]+f[k][j])
                    f[i][j]=f[i][k]+f[k][j];
    return f;
}

void init_graph(){
    ifstream ifs("graph.txt");
    g.resize(n+1);
    while(!ifs.eof()){
        int u,v,w;
        ifs>>u>>v>>w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    ifs.close();
}
void init_name(){
    ifstream ifs("name.txt");
    while(!ifs.eof()){
        int id;string name;
        ifs>>id>>name;
        names.insert({id,name});
    }
}
int main(){
    system("chcp 65001");
    init_graph();
    init_name();
    for(auto[id,name]:names)
        cout<<id<<"\t"<<name<<'\n';
    while(1){
        cout<<"你要从哪里出发,输入编号:\n";
        int s;cin>>s;
        auto res=dijkstra(s);
        for(int i=1;i<res.size();i++){
            cout<<"从 "<<names[s]<<" 到 "<<names[i]<<" 的最短路径为"<<res[i]<<'\n';
        }
    }
    
    return 0;
}