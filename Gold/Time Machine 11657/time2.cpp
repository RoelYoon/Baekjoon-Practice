#include <iostream>
#include <vector>
#include <queue>
#define ll long long
#define INF ((ll)1e18)
using namespace std;
struct Edge{
    int u,v;
    ll w;
    Edge(){}
    Edge(int u, int v, ll w):u(u),v(v),w(w){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll D,P,C,F; int S; cin>>D>>P>>C>>F>>S;
    --S;
    vector<Edge> edges;
    vector<vector<int>> graph(C);
    for(int i = 0; i < P; ++i){
        int u,v; cin>>u>>v;
        --u,--v;
        edges.emplace_back(u,v,-D);
        graph[u].push_back(i);
    }
    for(int i = 0; i < F; ++i){
        int u,v; ll w; cin>>u>>v>>w;
        --u,--v;
        edges.emplace_back(u,v,w-D);
        graph[u].push_back(edges.size()-1);
    }
    vector<ll> d(C,INF);
    d[S]=-D;
    for(int i = 0; i < C-1; ++i){
        bool newRelaxation = 0;
        for(int u = 0; u < C; ++u){
            for(int j = 0; j < graph[u].size(); ++j){
                Edge &e = edges[graph[u][j]];
                if(d[e.u]+e.w < d[e.v]){
                    d[e.v]=d[e.u]+e.w;
                    newRelaxation = 1;
                }
            }
        }
        if(!newRelaxation) break;
    }
    bool negativeCycle = 0;
    for(int u = 0; u < C; ++u){
        for(int i = 0; i < graph[u].size(); ++i){
            Edge &e = edges[graph[u][i]];
            if(d[e.u]+e.w < d[e.v]){
                negativeCycle = 1;
            }
        }
    }
    if(negativeCycle){
        cout<<"-1\n";
        return 0;
    }
    ll mx = 0;
    for(int i = 0; i < C; ++i){
        mx = max(mx,(d[i]>0?0:-d[i]));
    }
    cout<<mx<<"\n";
}