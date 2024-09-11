#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
class FlowNetwork{
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        Edge(){}
        Edge(int u, int v, int c):u(u),v(v),cap(c),flow(0){}
    };
    #define SS V-2
    #define ST V-1
    #define INF 1000000000
    int V;
    vector<int> level;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> saveDFS;
    bool BFS(){
        queue<int> q({SS});
        level.assign(V,-1); level[SS]=0;
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(cur==ST) break;
            for(int i = 0; i < graph[cur].size(); ++i){
                Edge &edge = edges[graph[cur][i]];
                if(edge.cap-edge.flow>0 && level[edge.v]==-1){
                    level[edge.v]=level[cur]+1;
                    q.push(edge.v);
                }
            }
        }
        return level[ST]!=-1;
    }
    int DFS(int cur, int f){
        if(cur==ST || f == 0) return f;
        for(int &i = saveDFS[cur]; i < graph[cur].size(); ++i){
            Edge &edge = edges[graph[cur][i]];
            if(level[edge.v]!=level[cur]+1) continue;
            int pushedFlow = DFS(edge.v, min(f,edge.cap-edge.flow));
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
    FlowNetwork(int v):V(v),level(V),graph(V),saveDFS(V){}
    void addEdge(int u, int v, int c){
        edges.emplace_back(u,v,c);
        graph[u].push_back(edges.size()-1);
        edges.emplace_back(v,u,0);
        graph[v].push_back(edges.size()-1);
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
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int c,d,v; cin>>c>>d>>v;
        FlowNetwork fn(v+2);
        vector<pair<string,string>> catPeople;
        vector<pair<string,string>> dogPeople;
        for(int i = 0; i < v; ++i){
            string v1,v2; cin>>v1>>v2;
            if(v1[0]=='C'){
                catPeople.emplace_back(v1,v2);
            }else{
                dogPeople.emplace_back(v1,v2);
            }
        }
        for(int i = 0; i < catPeople.size(); ++i){
            fn.addEdge(v,i,1);
        }
        for(int i = 0; i < dogPeople.size(); ++i){
            fn.addEdge(i+catPeople.size(),v+1,1);
        }
        for(int i = 0; i < catPeople.size(); ++i){
            for(int j = 0; j < dogPeople.size(); ++j){
                if(catPeople[i].first == dogPeople[j].second ||
                catPeople[i].second == dogPeople[j].first){
                    fn.addEdge(i,j+catPeople.size(),1);
                }
            }
        }
        cout<<v-fn.maxFlow()<<"\n";
    }
}