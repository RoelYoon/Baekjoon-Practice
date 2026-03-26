#include <iostream>
#include <vector>
using namespace std;
int children(vector<vector<int>> &graph, int x, int head){
    if(head==x) return 0;
    int cnt = 0;
    for(int i = 0; i < graph[head].size(); ++i){
        cnt+=children(graph, x, graph[head][i]);
    }
    return (!cnt?1:cnt);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<vector<int>> graph(n);
    int root = -1;
    for(int i = 0; i < n; ++i){
        int p; cin>>p;
        if(p==-1){root = i; continue;} 
        graph[p].push_back(i);
    }
    int x; cin>>x;
    cout<<children(graph, x, root)<<"\n";
}