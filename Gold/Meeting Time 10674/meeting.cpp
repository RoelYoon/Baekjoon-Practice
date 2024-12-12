#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
struct Edge{
    int u,v,bw,ew;
    Edge(){}
    Edge(int u, int v, int bw, int ew):u(u),v(v),bw(bw),ew(ew){}
};
int n,m;
vector<Edge> edges;
vector<vector<int>> graph;
unordered_set<int> bTimes;
bool DP[100][10000]{};
bool DP2[100][10000]{};
int minTime=1e9;
void findBTimes(int head, int time){
    if(head==n-1){
        bTimes.insert(time);
        return;
    }
    if(DP[head][time]) return;
    DP[head][time]=1;
    for(int i = 0; i < graph[head].size(); ++i){
        Edge &edge = edges[graph[head][i]];
        findBTimes(edge.v,time+edge.bw);
    }
}
void findMinTime(int head, int time){
    if(head==n-1){
        if(bTimes.find(time)!=bTimes.end()){
            minTime=min(minTime,time);
        }
        return;
    }
    if(DP2[head][time]) return;
    DP2[head][time]=1;
    for(int i = 0; i < graph[head].size(); ++i){
        Edge &edge = edges[graph[head][i]];
        findMinTime(edge.v,time+edge.ew);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    graph.resize(n);
    for(int i = 0; i < m; ++i){
        int a,b,bw,ew; cin>>a>>b>>bw>>ew;
        --a,--b;
        graph[a].push_back(edges.size());
        edges.emplace_back(a,b,bw,ew);
    }
    findBTimes(0,0);
    findMinTime(0,0);
    cout<<(minTime==1e9?"IMPOSSIBLE":to_string(minTime))<<"\n";
}