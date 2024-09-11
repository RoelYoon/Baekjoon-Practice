#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n,m,k;
class FlowNetwork{
    private:
    #define SS (V-3)
    #define ST (V-2)
    #define INF 1000000000
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        Edge(){}
        Edge(int u, int v, int c, int f):u(u),v(v),cap(c),flow(f){}
    };
    int V;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> level;
    vector<int> savedPointDFS;
    bool BFS(){
        queue<int> q({SS});
        level.assign(V,-1);
        level[SS]=0;
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(cur==ST) break;
            for(int i = 0; i < graph[cur].size(); i++){
                Edge &edge = edges[graph[cur][i]];
                if(edge.cap-edge.flow > 0 && level[edge.v]==-1){
                    level[edge.v]=level[cur]+1;
                    q.push(edge.v);
                }
            }
        }
        return level[ST]!=-1;
    }
    int DFS(int cur, int f){
        if(cur==ST || f==0) return f;
        for(int &i = savedPointDFS[cur]; i < graph[cur].size(); i++){
            Edge &edge = edges[graph[cur][i]];
            if(level[edge.v]!=level[cur]+1) continue;
            if(int pushedFlow = DFS(edge.v,min(f,edge.cap-edge.flow))){
                edge.flow+=pushedFlow;
                Edge &rEdge = edges[graph[cur][i]^1];
                rEdge.flow-=pushedFlow;
                return pushedFlow;
            }
        }
        return 0;
    }
    public:
    FlowNetwork(int v):V(v+3),graph(V),level(V){}
    void addEdge(int u, int v, int c){
        edges.emplace_back(u,v,c,0);
        graph[u].push_back(edges.size()-1);
        edges.emplace_back(v,u,0,0);
        graph[v].push_back(edges.size()-1);
    }
    int maxFlow(){
        int mf = 0;
        while(BFS()){
            savedPointDFS.assign(V,0);
            while(int f = DFS(SS,INF)){
                mf+=f;
            }
        }
        return mf;
    }
};
int main(){
    #define E_SS (n+m)
    #define E_ST (n+m+1)
    #define K_NODE (n+m+2)
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k; 
    FlowNetwork fn(n+m);
    fn.addEdge(E_SS,K_NODE,k);
    for(int i = 0; i < n; i++){
        fn.addEdge(E_SS,i,1);
        fn.addEdge(K_NODE,i,1);
    }
    for(int i = 0; i < m; i++){
        fn.addEdge(n+i,E_ST,1);
    }
    for(int i = 0; i < n; i++){
        int tasks; cin>>tasks;
        for(int j = 0; j < tasks; j++){
            int task; cin>>task; --task;
            fn.addEdge(i,n+task,1);
        }
    }
    cout<<fn.maxFlow()<<"\n";
}