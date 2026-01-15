#include <iostream>
#include <vector>
#include <set>
#define INF ((int)1e9)
using namespace std;
struct Edge{
    int u,v,w;
    Edge(){}
    Edge(int u, int v, int w):u(u),v(v),w(w){}
};
struct CMP{
    vector<int> &d;
    CMP(vector<int> &d):d(d){}
    bool operator()(const int v, const int v2) const {
        if(d[v]==d[v2]) return v<v2;
        return d[v]<d[v2];
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int V,E,S; cin>>V>>E>>S; --S;
    vector<vector<int>> graph(V);
    vector<Edge> edges(E);
    for(int i = 0; i < E; ++i){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
        --edges[i].u,--edges[i].v;
        graph[edges[i].u].push_back(i);
    }
    vector<int> d(V,INF);
    CMP cmp(d);
    set<int,CMP> pq(cmp);
    d[S]=0;
    pq.insert(S);
    while(!pq.empty()){
        int head = *pq.begin(); pq.erase(pq.begin());
        for(int i = 0; i < graph[head].size(); ++i){
            Edge &e = edges[graph[head][i]];
            if(d[head]+e.w < d[e.v]){
                pq.erase(e.v);
                d[e.v]=d[head]+e.w;
                pq.insert(e.v);
            }
        }
    }
    for(int i=0; i<V; ++i)
        cout<<(d[i]==INF?"INF":to_string(d[i]))<<"\n";
}