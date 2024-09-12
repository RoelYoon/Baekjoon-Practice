#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <sstream>
using namespace std;
struct Sentence{
    unordered_set<string> words;
    Sentence(){}
    void addString(string &s, unordered_set<string> &allWords){
        stringstream ss(s);
        string token;
        char delimiter = ' ';
        while(getline(ss,token,delimiter)){
            words.insert({token});
            allWords.insert({token});
        }
    }
};
class FlowNetwork{
    #define SS 0
    #define ST 1
    #define in(i) (i)
    #define out(i) (halfV+i)
    #define INF 1000000000
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
    vector<int> saveDFS;
    bool BFS(){
        queue<int> q({out(SS)});
        level.assign(V,-1); level[out(SS)]=0;
        while(!q.empty()){
            int cur = q.front(); q.pop();
            if(cur==ST) break;
            for(int i = 0; i < graph[cur].size(); ++i){
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
    FlowNetwork(int v):halfV(v),V(v*2),level(V),graph(V),saveDFS(V){}
    void addEdge(int u, int v, int c){
        edges.emplace_back(out(u),in(v),c);
        graph[out(u)].push_back(edges.size()-1);
        edges.emplace_back(in(v),out(u),0);
        graph[in(v)].push_back(edges.size()-1);
    }
    void splitEdge(int u, int c){
        edges.emplace_back(in(u),out(u),c);
        graph[in(u)].push_back(edges.size()-1);
        edges.emplace_back(out(u),in(u),0);
        graph[out(u)].push_back(edges.size()-1);
    }
    int maxFlow(){
        int mf = 0;
        while(BFS()){
            saveDFS.assign(V,0);
            while(int f = DFS(out(SS),INF)){
                mf+=f;
            }
        }
        return mf;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    for(int t=1; t<=T; ++t){
        int n; cin>>n;
        vector<Sentence> sentences(n);
        unordered_set<string> allWords;
        for(int i = 0; i < n; ++i){
            string s; getline(cin>>ws,s);
            sentences[i].addString(s,allWords);
        }
        FlowNetwork fn(n+allWords.size());
        for(int i = 0; i < n+allWords.size(); ++i){
            fn.splitEdge(i,(i<n ? INF : 1));
        }
        int id = n;
        for(unordered_set<string>::iterator it = allWords.begin(); it!=allWords.end(); ++it, ++id){
            for(int i = 0; i < n; ++i){
                if(sentences[i].words.find(*it)!=sentences[i].words.end()){
                    fn.addEdge(id,i,INF);
                    fn.addEdge(i,id,INF);
                }
            }
        }
        std::cout<<"Case #"<<t<<": "<<fn.maxFlow()<<"\n";
    }
}