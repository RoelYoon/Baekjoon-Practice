#include <iostream>
#include <vector>
#include <queue>
#define INF 1000000000
using namespace std;
class FlowNetwork{
    private:
    #define SS 0
    #define ST 1
    #define OUT(i) ((i)+n)
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        Edge(){}
        Edge(int u, int v, int c, int f):u(u),v(v),cap(c),flow(f){}
    };
    int n;
    int V;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> levels;
    vector<int> saveDFS;
    bool BFS(){
        queue<int> q({SS});
        levels.assign(V,-1);
        levels[SS]=0;
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(cur==ST) break;
            for(int i = 0; i < graph[cur].size(); ++i){
                Edge &edge = edges[graph[cur][i]];
                if(edge.cap - edge.flow > 0 && levels[edge.v]==-1){
                    levels[edge.v]=levels[cur]+1;
                    q.push(edge.v);
                }
            }
        }
        return levels[ST]!=-1;
    }
    int DFS(int cur, int f){
        if(cur==ST || f==0) return f;
        for(int &i = saveDFS[cur]; i < graph[cur].size(); ++i){
            Edge &edge = edges[graph[cur][i]];
            if(levels[edge.v]!=levels[cur]+1) continue;
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
    FlowNetwork(int n):n(n),V(2*n),graph(V){
        for(int i = 0; i < n; ++i){
            edges.emplace_back(i,OUT(i),i==SS || i==ST ? INF : 1,0);
            graph[i].push_back(edges.size()-1);
            edges.emplace_back(OUT(i),i,0,0);
            graph[OUT(i)].push_back(edges.size()-1);
        }   
    }
    int maxFlow(){
        int mf = 0;
        while(BFS()){
            saveDFS.assign(V,0);
            while(int f = DFS(SS,INF)){
                mf+=f;
            }
        }
        return mf;
    }
    void addEdge(int u, int v, int c){
        static bool forward = 1;
        edges.emplace_back(OUT(u),v,c,0);
        graph[OUT(u)].push_back(edges.size()-1);
        edges.emplace_back(v,OUT(u),0,0);
        graph[v].push_back(edges.size()-1);
        forward = !forward;
        if(forward){return;}
        addEdge(v,u,c);
    }
};
int main(){
    int n, p; cin>>n>>p;
    FlowNetwork fn(n);
    for(int i = 0; i < p; ++i){
        int u, v; cin>>u>>v; --u, --v;
        fn.addEdge(u,v,INF);
    }
    cout<<fn.maxFlow()<<"\n";
}