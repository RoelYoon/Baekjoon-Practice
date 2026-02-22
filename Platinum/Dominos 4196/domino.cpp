#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class UnionFind{
    int n;
    vector<int> rank;
    vector<int> par;
    int s;
    public:
    UnionFind(int n):s(n),n(n),rank(n),par(n){
        for(int i = 0; i < n; ++i){
            par[i]=i;
        }
    }  
    int find(int p){
        if(par[p]==p)
            return p;
        return par[p]=find(par[p]);
    }
    void merge(int a, int b){
        a = find(a);
        b = find(b);
        if(rank[a]<rank[b]){
            int t = a;
            a = b;
            b = t;
        }
        s-=par[a]!=par[b];
        par[b] = a;
        rank[a] += rank[a]==rank[b];
    }
    int size(){
        return s;
    }
};
void kosaraju(vector<vector<int>> &graph, vector<bool> &visited, UnionFind &uf, int g, int head){
    if(visited[head]){
        return;
    }
    visited[head]=1;
    uf.merge(g,head);
    for(int i = 0; i < graph[head].size(); ++i){
        kosaraju(graph, visited, uf, g, graph[head][i]);
    }
}
void DFS(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &postV, int head){
    if(visited[head]){
        return;
    }
    visited[head]=1;
    for(int i = 0; i < graph[head].size(); ++i){
        DFS(graph,visited,postV,graph[head][i]);
    } 
    postV.push_back(head);  
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n,E; cin>>n>>E;
        vector<vector<int>> graph(n);
        vector<vector<int>> transposed(n);
        for(int i = 0; i < E; ++i){
            int u,v; cin>>u>>v; --u,--v;
            graph[u].push_back(v);
            transposed[v].push_back(u);
        }
        vector<bool> visited(n);
        UnionFind uf(n);
        vector<int> postV;
        for(int i = 0; i < n; ++i){
            if(!visited[i]){
                DFS(graph, visited, postV, i);
            } 
        }
        reverse(postV.begin(), postV.end());
        visited.assign(n,0);
        for(int i = 0; i < postV.size(); ++i){
            if(!visited[postV[i]]){
                kosaraju(transposed, visited, uf, postV[i], postV[i]);
            }
        }
        vector<bool> in(n);
        int ans = uf.size();
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < graph[i].size(); ++j){
                if(in[uf.find(graph[i][j])] || uf.find(graph[i][j])==uf.find(i)){
                    continue;
                }
                in[uf.find(graph[i][j])]=1;
                --ans;
            }
        }
        cout<<ans<<"\n";
    }

}