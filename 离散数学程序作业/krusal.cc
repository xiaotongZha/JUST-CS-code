#include <iostream>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
const int INF=1e9;
int n,m;
struct edge{
    int v,w;
    edge(int v,int w):v(v),w(w){}
    bool operator<(const edge& oth)const{
		return w<oth.w;
	}
    bool operator>(const edge& oth)const{
		return w>oth.w;
	}
};
vector<vector<edge>>g;
int prim(int s){
    vector<bool>vis(n+1,0);
    vector<int>dis(n+1,INF);
    dis[s]=0;
    vis[s]=1;
    priority_queue<edge,vector<edge>,greater<edge>>pq;
    for(auto[v,w]:g[s]){
        dis[v]=w;
        pq.emplace(v,w);
    }
    int ans=0;
    int cnt=0;
    while (!pq.empty()){
        /* code */
        int u=pq.top().v,cost=pq.top().w;
        pq.pop();
        if(vis[u])
            continue;
        ans+=cost;
        cnt++;
        cout<<u<<'\n';
        vis[u]=1;
        for(auto[v,w]:g[u]){
            if(dis[v]>w){
                dis[v]=w;
                pq.emplace(v,w);
            }
        }
    } 
	return cnt==n-1?ans:-1;
}

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    g.resize(n+1);
    int u,v,w;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    cout<<prim(1)<<'\n';
	return 0;
}