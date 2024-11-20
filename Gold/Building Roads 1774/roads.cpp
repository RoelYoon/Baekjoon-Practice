#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#define ld long double
#define ll long long
#define pt complex<ll>
#define X real()
#define Y imag()
using namespace std;
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(pt p){
    return sqrt(sq(p));
}
struct Edge{
    int u,v;
    ld w;
    Edge(){}
    Edge(int u, int v, ld w):u(u),v(v),w(w){}
};
class UnionFind{
    int n;
    vector<int> rep,rank;
    public:
    UnionFind(int n):n(n),rep(n),rank(n){
        for(int i=0; i < n; ++i)
            rep[i]=i;
    }
    int find(int p){
        if(rep[p]==p) return p;
        return rep[p]=find(rep[p]);
    }
    void merge(int a, int b){
        a=find(a);
        b=find(b);
        if(rank[a]>rank[b]){
            rep[b]=a;
        }else if(rank[b]>rank[a]){
            rep[a]=b;
        }else{
            rep[b]=a;
            ++rank[a];
        }
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n>>m;
    vector<pt> points;
    vector<Edge> edges;
    for(int i = 0; i < n; ++i){
        ll x,y; cin>>x>>y;
        points.emplace_back(x,y);
    }
    UnionFind uf(n);
    for(int i = 0; i < m; ++i){
        int u,v; cin>>u>>v; --u,--v;
        uf.merge(u,v);
    }
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            edges.emplace_back(i,j,abs(points[i]-points[j]));
        }
    }
    sort(edges.begin(),edges.end(),[](const Edge &a, const Edge &b){
        return a.w<b.w;
    });
    ld mst=0;
    for(int i = 0; i < edges.size(); ++i){
        Edge &e = edges[i];
        if(uf.find(e.u)!=uf.find(e.v)){
            uf.merge(e.u,e.v);
            mst+=e.w;
        }
    }
    cout<<fixed<<setprecision(2)<<mst<<"\n";
}