#include <iostream>
#include <vector>
using namespace std;

typedef pair<int,int> edge;
typedef int vertex;
typedef vector<vector<vertex>> digraph;

bool dfs(digraph &G,vector<bool> &vis,vertex u,vertex target){
    if (u==target)
        return true;
    vis[u]=1;
    bool res=0;
    for(vertex v:G[u])
        if(not vis[v])
            res|=dfs(G,vis,v,target);
    return res;
}
bool has_selfLpop(digraph &G,vertex u){
    for(vertex v:G[u])
        if(v==u)
            return true;
    return false;
}
bool a_connect_b(digraph &G,vertex a,vertex b){
    if(a==b)
        return has_selfLpop(G,a);
    vector<bool>vis1(G.size()+1,0),vis2(G.size()+1,0); 
    return dfs(G,vis1,a,b) or dfs(G,vis2,b,a);
}  
bool a_reach_b(digraph &G,vertex a,vertex b){
    if(a==b)
        return has_selfLpop(G,a);
    vector<bool>vis(G.size()+1,0);
    return dfs(G,vis,a,b);
}
int main(){
    int vertex_num=5;
    edge edges[5]={{1, 2}, {2, 3}, {3, 4}, {4, 2}, {1, 5}};

    digraph G(vertex_num+1);
    for(auto[u,v]:edges)
        G[u].push_back(v);
    
    
    for(vertex a=1;a<=5;a++)
        for(vertex b=1;b<=5;b++)
            if(a_connect_b(G,a,b))
                printf("%d and %d is connected\n",a,b);
            else
                printf("%d and %d is not connected\n",a,b);

    for(vertex a=1;a<=5;a++)
        for(vertex b=1;b<=5;b++)
            if(a_reach_b(G,a,b))
                printf("%d is reachable to %d\n",a,b);
            else
                printf("%d is not reachable to %d\n",a,b);

    return 0;
}
