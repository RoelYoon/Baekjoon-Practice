#include <iostream>
#include <vector>
#include <set>
#define ll long long
#define INF ((ll) 1e18)
using namespace std;
struct State{
    int v;
    ll d;
    int k;
    State(){}
    State(ll d, int k, int v):v(v),d(d),k(k){}
    struct CMP{
        CMP(){}
        bool operator()(const State &a, const State &b) const {
            if(a.d == b.d){
                if(a.k==b.k){
                    return a.v<b.v;
                }
                return a.k>b.k;
            }
            return a.d<b.d;
        }
    };
};
struct Edge{
    int u,v;
    ll w;
    Edge(){}
    Edge(int u, int v, ll w):u(u),v(v),w(w){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,E,K; cin>>n>>E>>K;
    set<State,State::CMP> pq;
    vector<Edge> edges(E*2);
    vector<vector<int>> graph(n);
    for(int i = 0; i < E*2; i+=2){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
        --edges[i].u,--edges[i].v;
        edges[i^1].u = edges[i].v;
        edges[i^1].v = edges[i].u;
        edges[i^1].w = edges[i].w;
        graph[edges[i].u].push_back(i);
        graph[edges[i].v].push_back(i^1);
    }
    vector<vector<ll>> D(K+1,vector<ll>(n,INF));
    D[K][0]=0;
    pq.emplace(0,K,0);
    while(!pq.empty()){
        State s = *(pq.begin()); pq.erase(pq.begin());
        for(int i = 0; i < graph[s.v].size(); ++i){
            Edge &e = edges[graph[s.v][i]];
            if(D[s.k][s.v] + e.w < D[s.k][e.v]){
                set<State,State::CMP>::iterator it = pq.find(State(D[s.k][e.v],s.k,e.v));
                if(it!=pq.end()){
                    pq.erase(it);
                }
                D[s.k][e.v] = D[s.k][s.v]+e.w;
                pq.emplace(D[s.k][e.v],s.k,e.v);
            }
            if(s.k==0) continue;
            if(D[s.k][s.v] < D[s.k-1][e.v]){
                set<State,State::CMP>::iterator it = pq.find(State(D[s.k-1][e.v],s.k-1,e.v));
                if(it!=pq.end()){
                    pq.erase(it);
                }
                D[s.k-1][e.v] = D[s.k][s.v];
                pq.emplace(D[s.k-1][e.v],s.k-1,e.v);
            }
        }
    }
    ll ans = INF;
    for(int k = 0; k <= K; ++k){
        ans = min(ans,D[k][n-1]);
    }
    cout<<ans<<"\n";
}