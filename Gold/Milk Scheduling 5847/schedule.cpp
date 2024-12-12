#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    vector<int> times(n);
    vector<vector<int>> graph(n);
    vector<int> indegree(n);
    vector<int> dp(n);
    for(int i = 0; i < n; ++i)
        cin>>times[i];
    for(int i = 0; i < k; ++i){
        int a,b; cin>>a>>b; --a,--b;
        graph[a].push_back(b);
        ++indegree[b];
    }
    queue<int> q;
    for(int i = 0; i < n; ++i){
        if(!indegree[i]){
            q.push(i);
        }
        dp[i]=times[i];
    }
    while(!q.empty()){
        int head = q.front(); q.pop();
        for(int i = 0; i < graph[head].size(); ++i){
            --indegree[graph[head][i]];
            dp[graph[head][i]]=max(dp[graph[head][i]], dp[head] + times[graph[head][i]]);
            if(!indegree[graph[head][i]])
                q.push(graph[head][i]);
        }
    }
    int mx = dp[0];
    for(int i =1; i < n; ++i)
        mx=max(mx,dp[i]);
    cout<<mx<<"\n";
}