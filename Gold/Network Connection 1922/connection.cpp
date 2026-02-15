#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Edge{
    int u,v,w;
    Edge(){}
    Edge(int u, int v, int w):u(u),v(v),w(w){}
};
class UnionFind{
    int n;
    vector<int> par;
    vector<int> rank;
    public:
    UnionFind(int n):n(n),par(n),rank(n){
        for(int i = 0; i < n; ++i)
            par[i]=i;
    };
    int find(int p){
        if(par[p]==p){
            return p;
        }
        return par[p]=find(par[p]);
    }
    void merge(int a, int b){
        a = find(a);
        b = find(b);
        if(rank[a] < rank[b]){
            int t = a;
            a = b;
            b = t;
        }
        par[b]=a;
        if(rank[a]==rank[b])
            ++rank[a];
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m; cin>>n>>m;
    vector<Edge> edges(m);
    for(int i = 0; i < m; ++i){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
        --edges[i].u,--edges[i].v;
    }
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){
        return a.w < b.w;
    });
    UnionFind uf(n);
    long long cost = 0;
    for(int i = 0; i < m; ++i){
        Edge &e = edges[i];
        if(uf.find(e.u) != uf.find(e.v)){
            cost+=e.w;
            uf.merge(e.u,e.v);
        }
    }
    cout<<cost<<"\n";
}
