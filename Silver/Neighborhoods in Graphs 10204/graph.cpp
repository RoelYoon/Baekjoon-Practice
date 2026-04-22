#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
void DFS(vector<bool> &visited, vector<vector<int>> &graph, int &cnt, int d, int head){
    if(d>=3) return;
    cnt+=!visited[head];
    visited[head]=1;
    for(int i = 0; i < graph[head].size(); ++i){
        DFS(visited,graph,cnt,d+1,graph[head][i]);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n,E; cin>>n>>E;
        vector<vector<int>> graph(n);
        unordered_map<string, int> id;
        for(int i = 0; i < n; ++i){
            id.insert({"v"+to_string(i+1), i});
        }
        for(int i = 0; i < E; ++i){
            string s1,s2; cin>>s1>>s2;
            graph[id[s1]].push_back(id[s2]);
            graph[id[s2]].push_back(id[s1]);
        }
        string v; cin>>v;
        int cnt = -1;
        vector<bool> visited(n);
        DFS(visited,graph,cnt,0,id[v]);
        cout<<"The number of supervillains in 2-hop neighborhood of "<<v<<" is "<<cnt<<"\n";
    }
}