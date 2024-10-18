#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n,k,w; cin>>n>>k;
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
        cin>>w; --w;
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
        cout<<dp[w]<<"\n";
    }
}
/*
1
5 10
1 2 3 4 100
4 5
3 5
3 4
2 5
2 4
2 3
1 5
1 4
1 3
1 2
4
*/