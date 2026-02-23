#include <iostream>
#include <vector>
using namespace std;
void DFS(vector<vector<int>> &graph, vector<int> &depth, int head, int d){
    depth[head] = d;
    for(int i = 0; i < graph[head].size(); ++i){
        DFS(graph,depth,graph[head][i],d+1);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        vector<vector<int>> graph(n);
        vector<vector<int>> par(n,vector<int>(15,-1));
        for(int i = 0; i < n-1; ++i){
            int p,v; cin>>p>>v;
            --p,--v;
            par[v][0]=p;
            graph[p].push_back(v);    
        }
        int root = -1;
        for(int i = 0; i < n; ++i){
            if(par[i][0] == -1){
                par[i][0] = i;
                root = i;
            }
        }
        for(int k = 1; k <= 14; ++k){
            for(int i = 0; i < n; ++i){
                par[i][k] = par[par[i][k-1]][k-1];
            }
        }
        vector<int> depth(n);
        DFS(graph,depth,root,0); 
        int a,b; cin>>a>>b; --a,--b;
        if(depth[a] > depth[b]){
            int t = a;
            a = b;
            b = t;
        }
        int df = depth[b] - depth[a];
        for(int k = 0; k <= 14; ++k){
            if(df&(1<<k)){
                b = par[b][k];
            }
        }
        if(a==b){
            cout<<a+1<<"\n";
            continue;
        }
        for(int k = 14; k >= 0; --k){
            if(par[a][k] != par[b][k]){
                a = par[a][k];
                b = par[b][k];
            }
        }
        cout<<par[a][0]+1<<"\n";
    }
}