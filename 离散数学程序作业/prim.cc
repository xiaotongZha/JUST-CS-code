#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 500;
const int MAXM = 1e5;
int n,m;
struct edge{
	int u,v,w;
	bool operator<(const edge& oth)const{
		return w<oth.w;
	}
}e[MAXM];

int pa[MAXN];
void uf_init(){
	for(int i=1;i<=n;i++)pa[i]=i;
}
int uf_find(int x){
	if(x==pa[x])return x;
	pa[x]=uf_find(pa[x]);
	return pa[x];
}
void uf_merge(int i,int j){
	pa[uf_find(i)]=uf_find(j);
}

vector<vector<pair<int,int>>> minSpanTree;
int kruskal(){
	sort(e,e+m);
	int cnt=0,ans=0,idx=0;
	uf_init();
	while(idx<m){
		if(uf_find(e[idx].u)!=uf_find(e[idx].v)){
            minSpanTree[e[idx].u].push_back({e[idx].v,e[idx].w});
            minSpanTree[e[idx].v].push_back({e[idx].u,e[idx].w});
			uf_merge(e[idx].u,e[idx].v);
			ans+=e[idx].w;
			cnt++;
			if(cnt==n-1)break;
		}
		idx++;
	}
	return idx==m?-1:ans;
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++)
		cin>>e[i].u>>e[i].v>>e[i].w;
    minSpanTree.resize(n+1);
	int ans=kruskal();

    //打印生成树的所有边
    for(int u=1;u<=n;u++)
        for(auto [v,w]:minSpanTree[u])
            cout<<u<<' '<<v<<' '<<w<<'\n';
        
	if(ans==-1)cout<<"orz\n";
	else cout<<ans<<'\n';
	return 0;
}