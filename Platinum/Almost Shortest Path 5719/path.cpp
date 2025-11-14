#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define ll long long
#define INF ((ll) 1e18)
using namespace std;
struct Edge{
    int u,v;
    ll w;
    bool active=true;
    Edge(){}
    Edge(int u, int v, ll w):u(u),v(v),w(w){}
};
struct Node{
    int i;
    ll d;
    Node(){}
    Node(int i, ll d):i(i),d(d){}
    bool operator<(const Node &k) const {
        if(d==k.d)
            return i<k.i;
        return d<k.d;
    }
};
struct Path{
    ll w;
    int i;
    Path(){}
    Path(int i, ll w):i(i),w(w){}
};
int n,m,s,t;
ll BFS(vector<Edge> &edges, vector<vector<int>> &graph, vector<vector<Path>> &paths, vector<ll> &dist){
    set<Node> pq;
    dist[s] = 0;
    pq.emplace(s,0);
    while(!pq.empty()){
        Node cur = *(pq.begin());
        if(cur.i==t){
            // only cut shortest paths
            break;
        }
        pq.erase(pq.begin()); // pop
        for(int i = 0; i < graph[cur.i].size(); ++i){
            Edge &edge = edges[graph[cur.i][i]];
            if(!edge.active) continue;
            if(dist[edge.v] >= dist[cur.i] + edge.w){
                pq.erase({edge.v, dist[edge.v]});
                dist[edge.v] = dist[cur.i] + edge.w;
                pq.emplace(edge.v, dist[edge.v]);
                paths[edge.v].emplace_back(graph[cur.i][i], dist[edge.v]);
            }
        }
    }
    return dist[t];
}
void deactivate(vector<Edge> &edges, vector<bool> &visited, vector<vector<Path>> &paths, int head){
    if(visited[head]) return;
    visited[head]=1;
    ll minDist = INF;
    for(int i = paths[head].size()-1; i >= 0; --i){
        minDist = min(minDist,paths[head][i].w);
        if(paths[head][i].w > minDist) break;
        Edge &edge = edges[paths[head][i].i];
        edge.active = false;
        deactivate(edges, visited, paths, edge.u);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        cin>>n>>m;
        if(!n && !m) break;
        cin>>s>>t;
        vector<Edge> edges(m);
        vector<vector<int>> graph(n); 
        for(int i = 0; i < m; ++i){
            cin>>edges[i].u>>edges[i].v>>edges[i].w;
            graph[edges[i].u].push_back(i); //directed edge
        }
        vector<ll> dist(n,INF);
        vector<vector<Path>> paths(n);
        if(BFS(edges,graph,paths,dist) == INF){
            cout<<"-1\n";
            continue;
        }
        vector<bool> visited(n);
        deactivate(edges,visited,paths,t);
        dist.assign(n,INF);
        ll ans = BFS(edges,graph,paths,dist);
        cout<<(ans==INF?-1:ans)<<"\n";
    }
}
/*
7 9
0 6
0 1 1
0 2 1
0 3 2
0 4 3
1 5 2
2 6 4
3 6 2
4 6 4
5 6 1
0 0
*/