#include <iostream>
#include <vector>
#include <set>
#define ll long long
#define INF 1e18
using namespace std;
struct Edge{
    int u,v;
    ll w;
    Edge(){}
    Edge(int u, int v, ll w):u(u),v(v),w(w){}
};
int n,m,k;
vector<Edge> edges;
vector<vector<int>> graph;
bool valid(int x){
    struct State{
        int node;
        int kPass;
        State(){}
        State(int node, int k):node(node),kPass(k){}
        bool operator<(const State &k) const {
            if(kPass==k.kPass){
                return node<k.node;
            }return kPass<k.kPass;
        }
    };
    vector<ll> minKPass(n,INF);
    minKPass[0]=0;
    set<State> pq{State(0,0)};
    while(!pq.empty()){
        set<State>::iterator head = pq.begin();
        for(int i = 0; i < graph[head->node].size(); ++i){
            Edge &edge = edges[graph[head->node][i]];
            int nxtKPass = minKPass[head->node]+(edge.w>x);
            if(minKPass[edge.v]>nxtKPass){
                set<State>::iterator prev = pq.find(State(edge.v,minKPass[edge.v]));
                if(prev!=pq.end())
                    pq.erase(prev);
                minKPass[edge.v]=nxtKPass;
                pq.insert({edge.v,nxtKPass});
            }
        }
        pq.erase(head);
    }
    return minKPass[n-1]<=k;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    graph.resize(n);
    for(int i = 0; i < m; ++i){
        int u,v,w; cin>>u>>v>>w; --u,--v;
        graph[u].push_back(edges.size());
        edges.emplace_back(u,v,w);
        graph[v].push_back(edges.size());
        edges.emplace_back(v,u,w);
    }
    ll L=0,R=1e7;
    ll ans = -1;
    while(L<=R){
        ll mid = (L+R)/2;
        if(valid(mid)){
            //can we get lower?
            ans=mid;
            R=mid-1;
        }else{
            L=mid+1;
        }
    }
    cout<<ans<<"\n";
}