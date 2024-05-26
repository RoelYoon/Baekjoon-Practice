#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class FlowNetwork{
    private:
    #define SS 0
    #define ST 1
    #define IN(i) (i)
    #define OUT(i) (i+V)
    #define INF 1000000000
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        Edge(){}
        Edge(int u, int v, int c, int f):u(v),v(v),cap(c),flow(f){}
    };
    int V, GV;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> level;
    vector<int> savedPointDFS;
    bool BFS(){
        queue<int> q({0});
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
            int pushedFlow = DFS(edge.v,min(f,edge.cap-edge.flow));
            if(pushedFlow){
                edge.flow += pushedFlow;
                Edge &rEdge = edges[graph[cur][i]^1];
                rEdge.flow -= pushedFlow;
                return pushedFlow;
            }
        }
        return 0;
    }
    public:
    FlowNetwork(int v):V(v),GV(2*V),graph(GV),level(GV){
        edges.emplace_back(IN(0),OUT(0),INF,0);
        graph[IN(0)].push_back(edges.size()-1);
        edges.emplace_back(OUT(0),IN(0),INF,0);
        graph[OUT(0)].push_back(edges.size()-1);

        edges.emplace_back(IN(1),OUT(1),INF,0);
        graph[IN(1)].push_back(edges.size()-1);
        edges.emplace_back(OUT(1),IN(1),INF,0);
        graph[OUT(1)].push_back(edges.size()-1);
        for(int i = 2; i < V; ++i){
            edges.emplace_back(IN(i),OUT(i),1,0);
            graph[IN(i)].push_back(edges.size()-1);
            edges.emplace_back(OUT(i),IN(i),1,0);
            graph[OUT(i)].push_back(edges.size()-1);
        }
    }
    void addEdge(int u, int v, int c){
        // in-node
        edges.emplace_back(OUT(u),IN(v),c,0);
        graph[OUT(u)].push_back(edges.size()-1);
        edges.emplace_back(IN(v),OUT(u),c,0);
        graph[IN(v)].push_back(edges.size()-1);
    }
    int maxFlow(){
        int mf = 0;
        while(BFS()){
            savedPointDFS.assign(GV,0);
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
    int n,p; cin>>n>>p;
    FlowNetwork fn(n);
    for(int i = 0; i < p; ++i){
        int u,v; cin>>u>>v; --u, --v;
        fn.addEdge(u,v,INF);
    }
    cout<<fn.maxFlow()<<"\n";
}
/*
8 9
1 3
3 4
4 2
2 6
6 5
5 3
1 7
7 8
8 4
2

6 7
3 1
3 4
4 2
1 6
3 5
5 2
3 6
1
*/