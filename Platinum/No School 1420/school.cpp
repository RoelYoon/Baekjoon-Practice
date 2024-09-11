#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int dR[4]{-1,0,1,0};
int dC[4]{0,1,0,-1};
class FlowNetwork{
    #define INF 1000000000
    #define in(i) (i)
    #define out(i) (halfV+i)
    struct Edge{
        int u;
        int v;
        int cap;
        int flow;
        Edge(){}
        Edge(int u, int v, int c):u(u),v(v),cap(c),flow(0){}
    };
    int V;
    int halfV;
    vector<int> level;
    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> lastDFS;
    bool BFS(int s, int t){
        level.assign(V,-1); level[s]=0;
        queue<int> q({s});
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(cur==t) break;
            for(int i = 0; i < graph[cur].size(); ++i){
                Edge &edge = edges[graph[cur][i]];
                if(edge.cap-edge.flow > 0 && level[edge.v]==-1){
                    level[edge.v] = level[cur]+1;
                    q.push(edge.v);
                }
            }
        }
        return level[t]!=-1;
    }
    int DFS(int cur, int t, int f){
        if(cur==t || f==0) return f;
        for(int &i = lastDFS[cur]; i < graph[cur].size(); ++i){
            Edge &edge = edges[graph[cur][i]];
            if(level[edge.v]!=level[cur]+1) continue;
            int pushedFlow = DFS(edge.v,t,min(f,edge.cap-edge.flow));
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
    FlowNetwork(int v):V(2*v),halfV(v),graph(V),lastDFS(V){}
    void addEdge(int u, int v, int c){
        edges.emplace_back(out(u),in(v),c);
        graph[out(u)].push_back(edges.size()-1);
        edges.emplace_back(in(v),out(u),0);
        graph[in(v)].push_back(edges.size()-1);
    }
    void addSplitEdge(int u, int c){
        edges.emplace_back(in(u),out(u),c);
        graph[in(u)].push_back(edges.size()-1);
        edges.emplace_back(out(u),in(u),0);
        graph[out(u)].push_back(edges.size()-1);
    }
    int maxFlow(int s, int t){
        s = out(s);
        t = in(t);
        int mf = 0;
        while(BFS(s,t)){
            lastDFS.assign(V,0);
            while(int f = DFS(s,t,INF)){
                mf+=f;
            }
        }
        return mf;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R,C; cin>>R>>C;
    char board[105][105];
    FlowNetwork fn(R*C);
    int source, sink;
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            cin>>board[r][c];
            if(board[r][c]=='K') source = r*C+c;
            if(board[r][c]=='H') sink = r*C+c;
            fn.addSplitEdge(r*C+c,1);
        }
    }
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            if(board[r][c]=='#'){continue;}
            for(int i = 0; i < 4; ++i){
                int nxtR = r + dR[i];
                int nxtC = c + dC[i];
                if(nxtR>=0 && nxtR < R && nxtC >= 0 && nxtC < C && board[nxtR][nxtC]!='#'){
                    fn.addEdge(r*C+c,nxtR*C+nxtC,INF);
                    if(board[nxtR][nxtC]=='H' && board[r][c]=='K'){cout<<"-1\n"; return 0;}
                }
            }
        }
    }
    cout<<fn.maxFlow(source,sink)<<"\n";
}