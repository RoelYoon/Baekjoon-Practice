#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct MCMF{
    int mc;
    int mf;
    MCMF(int c, int f):mc(c),mf(f){}
};
class FlowNetwork{
    private:
    #define SS (V-2)
    #define ST (V-1)
    #define INF 1000000000
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        int w;
        Edge(int u, int v, int c, int w):u(u),v(v),cap(c),flow(0),w(w){}
        Edge(){}
    };
    int V;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> dist;
    vector<bool> visited;
    vector<int> savedPointDFS;
    int totalCost = 0;
    bool BFS(){
        queue<int> q({SS});
        dist.assign(V,INF);
        dist[SS]=0;
        visited[SS]=1;
        while(!q.empty()){
            int cur = q.front(); q.pop(); visited[cur]=0;
            for(int i = 0; i < graph[cur].size(); ++i){
                Edge &edge = edges[graph[cur][i]];
                if(edge.cap-edge.flow > 0 && dist[cur] + edge.w < dist[edge.v]){
                    dist[edge.v]=dist[cur]+edge.w;
                    if(!visited[edge.v]){
                        q.push(edge.v);
                        visited[edge.v]=1;
                    }
                }
            }
        }
        return dist[ST]!=INF;
    }
    int DFS(int cur, int f){
        if(cur==ST || f==0) return f;
        visited[cur]=1;
        for(int &i = savedPointDFS[cur]; i < graph[cur].size(); ++i){
            Edge &edge = edges[graph[cur][i]];
            if(visited[edge.v] || dist[edge.v]!=dist[cur]+edge.w) continue;
            int pushedFlow = DFS(edge.v,min(f,edge.cap-edge.flow));
            if(pushedFlow){
                totalCost+=edge.w*pushedFlow;
                edge.flow+=pushedFlow;
                Edge &rEdge = edges[graph[cur][i]^1];
                rEdge.flow-=pushedFlow;
                visited[cur]=0;
                return pushedFlow;
            }
        }
        visited[cur]=0;
        return 0;
    }
    public:
    FlowNetwork(int v):V(v),graph(V),visited(V),dist(V){}
    void addEdge(int u, int v, int c, int w){
        edges.emplace_back(u,v,c,w);
        graph[u].push_back(edges.size()-1);
        edges.emplace_back(v,u,0,-w);
        graph[v].push_back(edges.size()-1);
    }
    MCMF maxFlow(){
        int mf = 0;
        while(BFS()){
            savedPointDFS.assign(V,0);
            while(int f = DFS(SS,INF)){
                mf+=f;
            }
        }
        return MCMF(totalCost,mf);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n>>m;
    FlowNetwork fn(n+m+2);
    for(int i = 0; i < n; ++i){
        int k; cin>>k;
        fn.addEdge(n+m,i,1,0);
        for(int j = 0; j < k; ++j){
            int task, wage; cin>>task>>wage; --task;
            fn.addEdge(i,n+task,1,wage);
        }
    }
    for(int i = 0; i < m; ++i){
        fn.addEdge(i+n,n+m+1,1,0);
    }
    MCMF mcmf = fn.maxFlow();
    cout<<mcmf.mf<<"\n"<<mcmf.mc<<"\n";
}