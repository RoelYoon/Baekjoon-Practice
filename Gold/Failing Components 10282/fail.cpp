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
    bool operator()(const int &a, const int &b) const {
        if(d[a]==d[b]) return a<b;
        return d[a]<d[b];
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n,E,c; cin>>n>>E>>c;
        vector<Edge> edges(E);
        vector<vector<int>> graph(n);
        for(int i = 0; i < E; ++i){
            cin>>edges[i].v>>edges[i].u>>edges[i].w;
            --edges[i].u,--edges[i].v;
            graph[edges[i].u].push_back(i);
        }
        vector<int> d(n,INF);
        d[--c]=0;
        CMP cmp(d);
        set<int,CMP> pq(cmp);
        pq.insert(c);
        while(!pq.empty()){
            int head = *pq.begin();
            pq.erase(pq.begin());
            for(int i = 0; i < graph[head].size(); ++i){
                Edge &e = edges[graph[head][i]];
                if(d[e.u]+e.w < d[e.v]){
                    pq.erase(e.v);
                    d[e.v]=d[e.u]+e.w;
                    pq.insert(e.v);
                }
            }
        }
        int cnt = 0;
        int ans = 0;
        for(int i = 0; i < n; ++i){
            if(d[i]!=INF){
                ++cnt;
                ans=max(ans,d[i]);
            }
        }
        cout<<cnt<<" "<<ans<<"\n";
    }
}