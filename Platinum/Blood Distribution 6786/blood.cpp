#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Edge{
    int u;
    int v;
    int f;
    int c;
    Edge(){}
    Edge(int u, int v, int f, int c):u(u),v(v),f(f),c(c){}
};
class FlowNetwork{
    #define INF 1e9
    #define SS (n-2)
    #define ST (n-1)
    int n;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> dist; // for optimization: only move through nodes that increase distance from source
    vector<int> DFS_cache;
    // normal BFS for max flow only; bellman-ford for minimum cost max flow 
    bool BFS(){
        queue<int> q; q.push(SS);
        dist.assign(n,-1);
        dist[SS]=0;
        while(!q.empty()){
            int head = q.front(); q.pop();
            // check flow 
            if(head == ST) break;
            for(int i = 0; i < graph[head].size(); ++i){
                Edge &edge = edges[graph[head][i]];
                if(edge.c-edge.f > 0 && dist[edge.v]==-1){
                    q.push(edge.v);
                    dist[edge.v] = dist[head]+1;
                }
            }
        }
        return dist[ST] != -1; // visited sink node
    }
    int DFS(int head, int f){
        if(head==ST || !f) return f;
        for(int &i = DFS_cache[head]; i < graph[head].size(); ++i){
            Edge &edge = edges[graph[head][i]];
            if(dist[edge.v]!=dist[head]+1) continue;
            if(int pushedFlow = DFS(edge.v,min(f,edge.c-edge.f))){
                edge.f+=pushedFlow;
                Edge &residualEdge = edges[graph[head][i]^1];
                residualEdge.f -= pushedFlow;
                return pushedFlow;
            }
        }
        return 0;
    }
    public:
    FlowNetwork(int n):n(n+2),graph(n+2){}
    void addEdge(int u, int v, int c){
        graph[u].push_back(edges.size());
        edges.emplace_back(u,v,0,c);
        //residual c-f = 0-f
        graph[v].push_back(edges.size());
        edges.emplace_back(v,u,0,0);
    }
    int maxFlow(){
        int mf = 0;
        while(BFS()){
            DFS_cache.assign(n,0);
            while(int f = DFS(SS,INF)){
                mf+=f;
            }
        }
        return mf;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    FlowNetwork fn(16);
    vector<int> supply(8),patients(8);
    for(int i = 0; i < 8; ++i){
        cin>>supply[i];
        fn.addEdge(16,i,supply[i]);
    }
    bool map[8][8]{
        {1,1,1,1,1,1,1,1}, // O-
        {0,1,0,1,0,1,0,1}, // O+
        {0,0,1,1,0,0,1,1}, // A-
        {0,0,0,1,0,0,0,1}, // A+
        {0,0,0,0,1,1,1,1}, // B-
        {0,0,0,0,0,1,0,1}, // B+
        {0,0,0,0,0,0,1,1}, // AB-
        {0,0,0,0,0,0,0,1} // AB+
    };
    for(int j = 0; j < 8; ++j){
        cin>>patients[j];
        for(int i = 0; i < 8; ++i)
            if(map[i][j])
                fn.addEdge(i,j+8,INF);
        fn.addEdge(j+8,17,patients[j]);
    }
    cout<<fn.maxFlow()<<"\n";
}