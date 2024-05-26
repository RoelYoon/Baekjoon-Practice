#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
class UnionFind{
    private:
    int n;
    vector<int> unions;
    vector<int> ranks;
    public:
    UnionFind(int n):n(n),unions(n),ranks(n){
        for(int i = 0; i < n; i++)
            unions[i]=i;
    };
    int find(int a){
        if(unions[a]==a){return a;}
        return unions[a]=find(unions[a]);
    }
    void merge(int a, int b){
        a=find(a);
        b=find(b);
        if(ranks[b]<ranks[a]){
            int temp = b;
            b = a;
            a = temp;
        }//ranks[b]>ranks[a]
        unions[a]=b;
        if(ranks[a]==ranks[b])
            ++ranks[b];
    }
};
struct Edge{
    int u;
    int v;
    int L;
    Edge(){}
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, p; cin>>n>>p;
    vector<int> cs(n);
    UnionFind unions(n);
    ll cost = 10000;
    for(int i = 0; i < n; i++){
        cin>>cs[i];
        cost=min((int)cost,cs[i]);
    }
    vector<Edge> edges(p);
    for(int i = 0; i < p; i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].L;
        edges[i].u--; edges[i].v--;
    }
    sort(edges.begin(),edges.end(),[&](const Edge &a, const Edge &b){return (a.L*2+cs[a.u]+cs[a.v])<(b.L*2+cs[b.u]+cs[b.v]);});
    for(int i = 0; i < p; i++){
        if(unions.find(edges[i].u)!=unions.find(edges[i].v)){
            cost+=edges[i].L*2+cs[edges[i].u]+cs[edges[i].v];
            unions.merge(edges[i].u,edges[i].v);
        }
    }
    cout<<cost<<"\n";
}