#include <iostream>
#include <vector>
#include <queue>
#define MAX 85
#define NODE(r,c) (r*C + c)
using namespace std;
int R,C;
char room[MAX][MAX];
const int dirR[6]{-1,0,-1,0,1,1};
const int dirC[6]{-1,-1,1,1,-1,1};
bool inBounds(int r, int c){
    return r>=0 && r<R && c>=0 && c<C;
}
struct Node{
    int r;
    int c;
    Node(){}
    Node(int r, int c):r(r),c(c){}
};
class FlowNetwork{
    #define SS (V-2)
    #define ST (V-1)
    #define INF (1000000000)
    private:
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        Edge(){}
        Edge(int u, int v, int c):u(u),v(v),cap(c),flow(0){}
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
            for(int i = 0; i < graph[cur].size(); ++i){
                Edge &edge = edges[graph[cur][i]];
                if(edge.cap - edge.flow > 0 && level[edge.v]==-1){
                    level[edge.v]=level[cur]+1;
                    q.push(edge.v);
                }
            }
        }
        return level[ST]!=-1;
    }
    int DFS(int cur, int f){
        if(cur==ST || f==0){ return f; }
        for(int &i = savedPointDFS[cur]; i < graph[cur].size(); ++i){
            Edge &edge = edges[graph[cur][i]];
            if(level[edge.v]!=level[cur]+1) continue;
            if(int pushedFlow = DFS(edge.v, min(f,edge.cap-edge.flow))){
                edge.flow += pushedFlow;
                Edge &rEdge = edges[graph[cur][i]^1];
                rEdge.flow -= pushedFlow;
                return pushedFlow;
            }
        }
        return 0;
    }
    public:
    FlowNetwork(vector<Node> &nodes):V(nodes.size()+2),graph(V){
        for(int i = 0; i < nodes.size(); i++){
            if(room[nodes[i].r][nodes[i].c]=='x') continue;
            bool setU = nodes[i].c%2==0;
            if(setU){
                addEdge(SS,NODE(nodes[i].r,nodes[i].c),1);
                for(int j = 0; j < 6; j++){
                    int nxtR = nodes[i].r + dirR[j];
                    int nxtC = nodes[i].c + dirC[j];
                    if(inBounds(nxtR,nxtC) && room[nxtR][nxtC]=='.'){
                        addEdge(NODE(nodes[i].r,nodes[i].c),NODE(nxtR,nxtC),INF);
                    }
                }
            }
            if(!setU){
                addEdge(NODE(nodes[i].r,nodes[i].c),ST,1);
            }
        }
    }
    void addEdge(int u, int v, int c){
        edges.emplace_back(u,v,c);
        graph[u].push_back(edges.size()-1);
        edges.emplace_back(v,u,0);
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    int K; cin>>K;
    while(K--){
        cin>>R>>C;
        vector<Node> nodes;
        int nodeCount = 0;
        for(int r = 0; r < R; r++){
            for(int c = 0; c < C; c++){
                cin>>room[r][c];
                nodes.emplace_back(r,c);
                nodeCount+=room[r][c]=='.';
            }
        }
        FlowNetwork fn(nodes);
        cout<<nodeCount-fn.maxFlow()<<"\n";
    }
}