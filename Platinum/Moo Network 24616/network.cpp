#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
#define MAX 100005
using namespace std;
int n;
int xs[MAX];
int ys[MAX];
class UnionFind{
    private:
    int parents[MAX];
    int ranks[MAX]{};
    public:
    UnionFind(){
        for(int i = 0; i < n; i++){
            parents[i]=i;
        }
    }
    int find(int a){
        if(parents[a]==a){return a;}
        return parents[a]=find(parents[a]);
    }
    void merge(int a, int b){
        a=find(a);
        b=find(b);
        if(ranks[a]<ranks[b]){
            parents[a]=b;
        }else if(ranks[a]>ranks[b]){
            parents[b]=a;
        }else{
            parents[b]=a;
            ranks[a]++;
        }
    }
};
inline ll cost(ll u, ll v){
    return (ll)abs((ll)xs[u]-(ll)xs[v])*(ll)abs((ll)xs[u]-(ll)xs[v]) + (ll)abs((ll)ys[u]-(ll)ys[v])*(ll)abs((ll)ys[u]-(ll)ys[v]);
}
struct Edge{
    int u;
    int v;
    ll c;
    Edge(int u,int v):u(u),v(v){
        c=cost(u,v);
    } 
    Edge():u(-1),v(-1),c(-1){}
};
int main(){
    cin>>n;
    UnionFind unions;
    vector<int> cows(n);
    for(int i = 0; i < n; i++){
        cin>>xs[i]>>ys[i];
        cows[i]=i;
    }
    sort(cows.begin(),cows.end(),[](const int &a, const int &b){return xs[a]>xs[b];});
    ll totalCost=0;
    vector<Edge> edges;
    int deg = 25;
    for(int i = 0; i < n; i++){
        for(int j = i; j < i+deg && j < n; j++){
            edges.push_back(Edge(cows[i],cows[j]));
        }
        for(int j = i; j >= i-deg && j>=0; j--){
            edges.push_back(Edge(cows[i],cows[j]));
        }
    }
    sort(edges.begin(),edges.end(),[](const Edge &a, const Edge &b){return a.c < b.c;});
    int numTaken = 0;
    for(Edge &e : edges){
        if(unions.find(e.u)==unions.find(e.v)){continue;}
        unions.merge(e.u,e.v);
        totalCost+=e.c;
        if(++numTaken==n-1){break;}
    }
    cout<<totalCost<<"\n";
}