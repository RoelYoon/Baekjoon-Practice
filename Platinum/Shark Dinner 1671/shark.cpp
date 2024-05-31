#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Shark{
    int a;
    int b;
    int c;
    Shark(){}
    Shark(int a, int b, int c):a(a),b(b),c(c){}
};
inline bool canEat(Shark &a, Shark &b){
    return a.a >= b.a && a.b >= b.b && a.c >= b.c;
}
class FlowNetwork{
    private:
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        Edge(){}
        Edge(int u, int v, int c, int f):u(u),v(v),cap(c),flow(f){}
    };
    #define SS V-2
    #define ST V-1
    #define SEC(i) ((i)+n)
    #define THD(i) ((i)+2*n)
    #define INF 1000000000
    int n;
    int V;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> levels;
    vector<int> DFSsave;
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
        if(cur==ST || f==0){ return f; }
        for(int &i = DFSsave[cur]; i < graph[cur].size(); ++i){
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
    FlowNetwork(vector<Shark> &sharks):n(sharks.size()),V(sharks.size()*3+2),graph(V){
        for(int i = 0; i < n; ++i){
            addEdge(SS,i,1);
            addEdge(SS,SEC(i),1);
            addEdge(THD(i),ST,1);
            for(int j = i+1; j < n; ++j){
                if(canEat(sharks[i],sharks[j])){
                    addEdge(i,THD(j),1);
                    addEdge(SEC(i),THD(j),1);
                }else if(canEat(sharks[j],sharks[i])){
                    addEdge(j,THD(i),1);
                    addEdge(SEC(j),THD(i),1);
                }
            }
        }
    }
    void addEdge(int u, int v, int c){
        edges.emplace_back(u,v,c,0);
        graph[u].push_back(edges.size()-1);
        edges.emplace_back(v,u,0,0);
        graph[v].push_back(edges.size()-1);
    }
    int maxFlow(){
        int mf = 0;
        while(BFS()){
            DFSsave.assign(V,0);
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
    int n; cin>>n;
    vector<Shark> sharks(n);
    for(int i = 0; i < n; ++i){
        cin>>sharks[i].a>>sharks[i].b>>sharks[i].c;
    }
    FlowNetwork fn(sharks);
    cout<<n-fn.maxFlow()<<"\n";
}