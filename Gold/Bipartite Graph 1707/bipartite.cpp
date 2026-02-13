#include <iostream>
#include <vector>
using namespace std;
void DFS(vector<int> &color, vector<vector<int>> &graph, bool &b, int head) {
    for(int i = 0; i < graph[head].size(); ++i) {
        if(color[graph[head][i]] == color[head]){
            b = 0;
            return;
        }
        if(!color[graph[head][i]]) {
            color[graph[head][i]] = color[head]==1?2:1;
            DFS(color, graph, b, graph[head][i]);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n,e; cin>>n>>e;
        vector<vector<int>> graph(n);
        vector<int> color(n);
        for(int i = 0; i < e; ++i){
            int u,v; cin>>u>>v; --u,--v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        bool bipartite = 1;
        for(int i = 0; i < n; ++i) {
            if(color[i]!=0) continue;
            if(!bipartite) break;
            color[i] = 1;
            DFS(color, graph, bipartite, i);
    
        }
        cout<<(bipartite?"YES\n":"NO\n");   
    }
}
