#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Prerequisite{
    int part;
    int count;
    Prerequisite(int p, int c):part(p),count(c){};
};
int n,m;
void DFS(vector<vector<int>> &graph, bool visited[105],vector<int>& topOrder, int head){
    if(visited[head])
        return;
    visited[head]=true;
    for(int i = 0; i < graph[head].size(); i++)
        DFS(graph,visited,topOrder,graph[head][i]);
    topOrder.push_back(head);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    int weight[105][105];
    vector<vector<int>> graph(n+1);
    vector<vector<int>> residualGraph(n+1);
    for(int i = 0; i < m; i++){
        int x,y,k;
        cin>>x>>y>>k;
        graph[x].push_back(y);
        residualGraph[y].push_back(x);
        weight[x][y] = k;
    }
    vector<int> topOrder;
    bool visited[105]{};
    DFS(graph,visited,topOrder,n);
    int prerequisites[105][105]{};
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < residualGraph[topOrder[i]].size(); j++){
            for(int k = 1; k < n; k++)
                prerequisites[residualGraph[topOrder[i]][j]][k]+=(prerequisites[topOrder[i]][k]*weight[residualGraph[topOrder[i]][j]][topOrder[i]]);
            prerequisites[residualGraph[topOrder[i]][j]][topOrder[i]]=weight[residualGraph[topOrder[i]][j]][topOrder[i]];
        }
    }
    for(int i = 1; i < n; i++)
        if(graph[i].empty())
            cout<<i<<" "<<prerequisites[n][i]<<"\n";
}