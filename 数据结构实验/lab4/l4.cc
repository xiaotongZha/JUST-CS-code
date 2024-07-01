#include <iostream>
#include <vector>
#include <functional>
#include <queue>
using namespace std;

typedef pair<int,int> edge;

class Graph{
public:
    Graph(vector<edge> &es){
        vertexNum=es.size();
        g.resize(vertexNum);
        for(auto[u,v]:es){
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    void dfs(){
        vector<bool>vis(vertexNum,0);
        function<void(int,vector<bool>&)> _dfs=[&](int u,vector<bool>&vis){
            vis[u]=1;
            cout<<u<<' ';
            for(int v:g[u])
                if(!vis[v])
                    _dfs(v,vis);
        };
        _dfs(0,vis);
        cout<<'\n';
    }
    void bfs(){
        queue<int>q;
        q.push(0);
        vector<bool>vis(vertexNum,0);
        vis[0]=1;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            cout<<u<<' ';
            for(int v:g[u])
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                }
        }
        cout<<'\n';
    }

private:
    vector<vector<int>> g;
    int vertexNum;
};

int main(){
    vector<edge> es{{0,1},{0,2},{0,5},{1,2},{2,3},{2,4},{3,4},{3,5}};
    Graph g(es);
    cout << "DFS Traversal: ";
    g.dfs();
    cout << "BFS Traversal: ";
    g.bfs();

    return 0;
}