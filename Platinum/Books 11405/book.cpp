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
    vector<int> demand(n);
    vector<int> supply(m);
    vector<vector<int>> c(m,vector<int>(n));
    for(int i = 0; i < n; ++i){
        cin>>demand[i];
    }
    for(int i = 0; i < m; ++i){
        cin>>supply[i];
    }
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            cin>>c[i][j];
        }
    }
    FlowNetwork fn(n+m+2);
    for(int i = 0; i < n; ++i){
        fn.addEdge(n+m,i,demand[i],0);
    }
    for(int i = n; i < n+m; ++i){
        fn.addEdge(i,n+m+1,supply[i-n],0);
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            fn.addEdge(i,j+n,INF,c[j][i]);
        }
    }
    cout<<fn.maxFlow().mc<<"\n";
}