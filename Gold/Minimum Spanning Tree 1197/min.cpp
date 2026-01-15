#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct UnionFind{
    int n;
    vector<int> par;
    vector<int> rank;
    UnionFind(int n):n(n),par(n),rank(n){
        for(int i = 0; i < n; ++i)
            par[i]=i;
    }
    int find(int p){
        if(par[p]==p) return p;
        return par[p]=find(par[p]);
    }
    void merge(int a, int b){
        a=find(a);
        b=find(b);
        if(a!=b){
            if(rank[a]<rank[b]){ // assert rank[a]>rank[b]
                int t=a;
                a=b;
                b=t;
            }
            par[b]=a;
            if(rank[a]==rank[b])
                ++rank[a];
        }
    }
};
struct Edge{
    int u;
    int v;
    int w;
    Edge(){}
    Edge(int u, int v, int w):u(u),v(v),w(w){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int V,E; cin>>V>>E;
    UnionFind uf(V);
    vector<Edge> edges;
    for(int i = 0; i < E; ++i){
        int u,v,w; cin>>u>>v>>w;
        edges.emplace_back(u-1,v-1,w);
    }
    sort(edges.begin(),edges.end(),[](const Edge&a, const Edge&b){
        return a.w<b.w;
    });
    int minW = 0;
    for(int i = 0; i < E; ++i){
        if(uf.find(edges[i].u)!=uf.find(edges[i].v)){
            minW+=edges[i].w;
            uf.merge(edges[i].u,edges[i].v);
        }
    }
    cout<<minW<<"\n";
}