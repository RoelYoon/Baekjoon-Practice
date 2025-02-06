#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct MCMF{
    int mc,mf;
    MCMF(int c, int f):mc(c),mf(f){}
};
struct Edge{
    int u,v,flow,cap,w;
    Edge(int u, int v, int c, int w):u(u),v(v),flow(0),cap(c),w(w){}
};
class FlowNetwork{
    #define SS n-2
    #define ST n-1
    #define INF 1e9
    int n;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> cacheDFS;
    vector<int> dist;
    vector<bool> visited;
    inline int weight(int w){
        return (!w?0:(20-abs(w))*(w<0?-1:1));
    }
    bool BFS(int source){
        queue<int> q({source});
        dist.assign(n,INF);
        dist[source]=0;
        while(!q.empty()){
            int top = q.front(); q.pop(); visited[top]=0;
            for(int i = 0; i < graph[top].size(); ++i){
                Edge &edge = edges[graph[top][i]];
                if(edge.cap-edge.flow>0 && dist[edge.v] > dist[top]+weight(edge.w)){
                    dist[edge.v]=dist[top]+weight(edge.w);
                    if(!visited[edge.v]){
                        visited[edge.v]=1;
                        q.push(edge.v);
                    }
                }
            }
        }
        return dist[ST]!=INF;
    }
    int DFS(int head, int flow, int &cost){
        if(head==ST || !flow) return flow;
        visited[head]=1;
        for(int &i = cacheDFS[head]; i < graph[head].size(); ++i){
            Edge &edge = edges[graph[head][i]];
            if(visited[edge.v] || dist[edge.v]!=dist[head]+weight(edge.w)) continue;
            if(int pushedFlow = DFS(edge.v,min(flow,edge.cap-edge.flow),cost)){
                edge.flow+=pushedFlow;
                Edge &rEdge = edges[graph[head][i]^1];
                rEdge.flow-=pushedFlow;
                cost+=edge.w;
                visited[head]=0;
                return pushedFlow;
            }
        }
        visited[head]=0;
        return 0;
    }
    public:
    FlowNetwork(int n):n(n),graph(n),cacheDFS(n),dist(n),visited(n){}
    void addEdge(int u, int v, int c, int w){
        edges.emplace_back(u,v,c,w);
        graph[u].push_back(edges.size()-1);
        edges.emplace_back(v,u,0,-w);
        graph[v].push_back(edges.size()-1);
    }
    MCMF maxFlow(){
        int mf=0,mc=0;
        while(BFS(SS)){
            cacheDFS.assign(n,0);
            while(int f = DFS(SS,INF,mc))
                mf+=f;
        }
        return MCMF(mc,mf);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        int n,m;
        cin>>n>>m;
        if(!n && !m) break;
        FlowNetwork fn(n+m+2);
        for(int i = 0; i < n; ++i){
            int p; cin>>p;
            fn.addEdge(m+i,n+m+1,p,0);
        }
        for(int i = 0; i < m; ++i){
            fn.addEdge(n+m,i,1,0);
            int y; cin>>y;
            for(int j = 0; j < 4; ++j){
                int job; cin>>job;
                fn.addEdge(i,m+job,1,4*(y-1)+(4-j));
            }
        }
        cout<<fn.maxFlow().mc<<"\n";
    }
}