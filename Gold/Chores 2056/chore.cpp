#include <iostream>
#include <vector>
using namespace std;
vector<int> times;
vector<vector<int>> graph;
vector<int> DP;
int time(int head){
    if(DP[head]!=-1) return DP[head];
    int mxTime = 0;
    for(int i = 0; i < graph[head].size(); ++i){
        mxTime = max(mxTime,time(graph[head][i]));
    }
    return DP[head]=mxTime+times[head];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    times.resize(n);
    graph.resize(n);
    DP.assign(n,-1);
    for(int i = 0; i < n; ++i){
        int t,m; cin>>times[i]>>m;
        while(m--){
            int p; cin>>p; --p;
            graph[p].push_back(i);
        }
    }
    int ans = 0;
    for(int i = 0; i < n; ++i)
        ans = max(ans,time(i));
    cout<<ans<<"\n";
}