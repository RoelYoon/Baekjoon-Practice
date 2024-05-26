#include <iostream>
#include <vector>
#include <queue>
using namespace std;
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
        Edge(int u, int v, int c, int f):u(u),v(v),cap(c),flow(f){}
        Edge(){}
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
            int pushedFlow = DFS(edge.v,min(f,edge.cap-edge.flow));
            if(pushedFlow){
                edge.flow+=pushedFlow;
                Edge &rEdge = edges[graph[cur][i]^1];
                rEdge.flow-=pushedFlow;
                return pushedFlow;
            }
        }
        return 0;
    }
    public:
    FlowNetwork(int v):V(v),graph(V),level(V){}
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
    #define E_SS (n+d)
    #define E_ST (n+d+1)
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k,d; cin>>n>>k>>d;
    FlowNetwork fn(n+d+2);
    for(int i = 0; i < n; i++){
        fn.addEdge(E_SS,i,k);
    }
    for(int i = 0; i < d; i++){
        int dLim; cin>>dLim;
        fn.addEdge(n+i,E_ST,dLim);
    }
    for(int i = 0; i < n; i++){
        int dishNum; cin>>dishNum;
        for(int j = 0; j < dishNum; j++){
            int dish; cin>>dish; --dish;
            fn.addEdge(i,n+dish,1);
        }
    }
    cout<<fn.maxFlow()<<"\n";
}