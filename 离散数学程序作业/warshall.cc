#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
#define N 100

template<class Container>
void init_G(Container &c,int n){
    bool x;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>x; 
            c[i][j]=x; 
        }
    }
}
template<class Container>
void print_G(Container &G,int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<G[i][j]<<' ';
        cout<<'\n';
    }
}

void warshall(vector<vector<int>> &G){
    int n=G.size();
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                G[i][j]|=G[i][k]&G[k][j];
}

void warshall(bitset<N>* G,int n){
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            if(G[i][k])
                G[i]|=G[k];
}

int main(){
    int n;cin>>n;
    //vector<vector<int>> G(n,vector<int>(n));
    bitset<N>G[N];
    init_G(G,n);
    warshall(G,n);
    print_G(G,n);
    return 0;
}
