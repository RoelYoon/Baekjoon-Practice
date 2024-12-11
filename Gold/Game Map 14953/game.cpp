#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> graph;
int DP[100000]{};
int findSize(int head, int neighbors){
    if((int)graph[head].size() <= neighbors) return 0;
    if(DP[head]) return DP[head];
    int mxSize = 0;
    for(int i = 0; i < graph[head].size(); ++i){
        mxSize=max(mxSize,findSize(graph[head][i],graph[head].size()));
    }
    return DP[head]=mxSize+1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n>>m;
    graph.resize(n);
    for(int i=0; i < m; ++i){
        int a,b; cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int maxSize = 0;
    for(int i = 0; i < n; ++i){
        maxSize=max(maxSize,findSize(i,-1));
    }
    cout<<maxSize<<"\n";
}