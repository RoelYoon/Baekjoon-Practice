/*
Faster solution
*/
#include <iostream>
#include <vector>
#include <queue>
#define INF ((int)1e9)
using namespace std;
struct Edge{
    int u,v,w;
    Edge(){}
    Edge(int u, int v, int w):u(u),v(v),w(w){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int V,m,w; cin>>V>>m>>w;
        vector<Edge> edges(m*2+w);
        vector<vector<int>> graph(V);
        for(int i = 0; i < m; ++i){
            cin>>edges[i].u>>edges[i].v>>edges[i].w;
            --edges[i].u; --edges[i].v;
            edges[m+i].u = edges[i].v;
            edges[m+i].v = edges[i].u;
            edges[m+i].w = edges[i].w;
            graph[edges[i].u].push_back(i);
            graph[edges[i].v].push_back(m+i);
        }
        for(int i = 0; i < w; ++i){
            cin>>edges[2*m+i].u>>edges[2*m+i].v>>edges[2*m+i].w;
            --edges[2*m+i].u; --edges[2*m+i].v;
            edges[2*m+i].w*=-1;
            graph[edges[2*m+i].u].push_back(2*m+i);
        }
        vector<int> d(V,0);
        queue<int> q;
        vector<bool> inQ(V);
        vector<int> loops(V);
        for(int i = 0; i < V; ++i)
            q.push(i);
        while(!q.empty()){
            int head = q.front(); q.pop();
            inQ[head]=0;
            if(loops[head]++==V) break;
            for(int i = 0; i < graph[head].size(); ++i){
                Edge &e = edges[graph[head][i]];
                if(d[e.u]+e.w < d[e.v]){
                    d[e.v]=d[e.u]+e.w;
                    if(!inQ[e.v]){
                        q.push(e.v);
                    }
                }
            }
        }
        bool negativeCycle = 0;
        for(int u = 0; u < V; ++u){
            for(int i = 0; i < graph[u].size(); ++i){
                Edge &e = edges[graph[u][i]];
                if(d[e.u]+e.w < d[e.v]){
                    negativeCycle=1;
                }
            }
        }
        cout<<(negativeCycle?"YES\n":"NO\n");
    }
}