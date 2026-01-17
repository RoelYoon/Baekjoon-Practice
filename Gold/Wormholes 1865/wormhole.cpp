#include <iostream>
#include <vector>
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
        vector<int> d(V,INF);
        bool newRelaxation = 0;
        for(int i = 0; i < V-1; ++i){
            newRelaxation=0;
            for(int u = 0; u < V; ++u){
                for(int j = 0; j < graph[u].size(); ++j){
                    Edge &e = edges[graph[u][j]];
                    if(d[e.u]+e.w < d[e.v]){
                        d[e.v]=d[e.u]+e.w;
                        newRelaxation=1;
                    }
                }
            }
            if(!newRelaxation) break;
        }
        newRelaxation=0;
        for(int u = 0; u < V; ++u){
            for(int j = 0; j < graph[u].size(); ++j){
                Edge &e = edges[graph[u][j]];
                if(d[e.u]+e.w < d[e.v]){
                    newRelaxation=1;
                }
            }
        }
        cout<<(newRelaxation?"YES\n":"NO\n");
    }
}