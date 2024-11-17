#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>
#include <vector>
#include <queue>
#define ld long double
#define ppt complex<ld>
#define X real()
#define Y imag()
#define EPS 1e-12L
using namespace std;
ld sq(ppt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(ppt p){
    return sqrt(sq(p))/5.0L;
}
struct Edge{
    int u,v;
    ld w;
    Edge(){}
    Edge(int u, int v, ld w):u(u),v(v),w(w){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ld a,b,c,d;
    cin>>a>>b>>c>>d;
    ppt start(a,b),end(c,d);
    int n; cin>>n;
    vector<ppt> cannons;
    for(int i = 0; i < n; ++i){
        ld x,y; cin>>x>>y;
        cannons.emplace_back(x,y);
    }
    vector<ppt> points(cannons.begin(),cannons.end());
    vector<Edge> edges;
    points.push_back(start),points.push_back(end);
    int startI=points.size()-2,endI=points.size()-1;
    vector<vector<int>> graph(100000);
    edges.emplace_back(startI,endI,abs(end-start));
    graph[startI].emplace_back(edges.size()-1);
    for(int i = 0; i < n; ++i){
        // walk start to cannon
        edges.emplace_back(startI,i,abs(cannons[i]-start));
        graph[startI].push_back(edges.size()-1);
        // walk cannon to end
        edges.emplace_back(i,endI,abs(end-cannons[i]));
        graph[i].push_back(edges.size()-1);
        // fire cannon to end
        points.push_back(cannons[i]+polar(50.0L,arg(end-cannons[i])));
        edges.emplace_back(i,points.size()-1,2.0L);
        graph[i].push_back(edges.size()-1);
        for(int j = 0; j < n; ++j){
            if(i==j) continue;
            //walking cannon to cannon
            edges.emplace_back(i,j,abs(cannons[j]-cannons[i]));
            graph[i].push_back(edges.size()-1);
            //fire cannon to cannon
            points.push_back(cannons[i]+polar(50.0L,arg(cannons[j]-cannons[i])));
            edges.emplace_back(i,points.size()-1,2.0L);
            graph[i].push_back(edges.size()-1);
        }
    }
    // connect landing points
    for(int i = n+2; i < points.size(); ++i){
        // landing point to end
        edges.emplace_back(i,endI,abs(end-points[i]));
        graph[i].push_back(edges.size()-1);
        // landing point to cannons
        for(int j = 0; j < n; ++j){
            edges.emplace_back(i,j,abs(cannons[j]-points[i]));
            graph[i].push_back(edges.size()-1);
        }
    }
    vector<ld> dist(points.size(),1e18L); dist[startI]=0;
    struct Pair{
        ld d;
        int v;
        Pair(){}
        Pair(ld d, int v):d(d),v(v){};
    };
    auto cmp = [](const Pair &a, const Pair &b){return a.d>b.d;};
    priority_queue<Pair,vector<Pair>,decltype(cmp)> pq(cmp);
    pq.emplace(0,startI);
    while(!pq.empty()){
        Pair head=pq.top(); pq.pop();
        if(head.d>dist[head.v]) continue;
        for(int i = 0; i < graph[head.v].size(); ++i){
            Edge &edge = edges[graph[head.v][i]];
            if(dist[edge.v]>dist[head.v]+edge.w){
                dist[edge.v]=dist[head.v]+edge.w;
                pq.emplace(dist[edge.v],edge.v);
            }
        }
    }
    cout<<fixed<<setprecision(6)<<dist[endI]<<"\n";
}