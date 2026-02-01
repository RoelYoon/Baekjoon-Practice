#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int dirR[4]{0,1,0,-1};
const int dirC[4]{1,0,-1,0};
int n;
void DFS(vector<vector<bool>> &graph, int& l, int r, int c){
    if(!graph[r][c]) return;
    ++l;
    graph[r][c]=0;
    for(int i = 0; i < 4; ++i){
        int nr = r+dirR[i];
        int nc = c+dirC[i];
        if(nr>=0 && nr<n && nc>=0 && nc<n){
            DFS(graph,l,nr,nc);
        }
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    vector<vector<bool>> graph(n,vector<bool>(n));
    for(int r = 0; r < n; ++r){
        string s; cin>>s;
        for(int c = 0; c< n; ++c){
            graph[r][c]=s[c]=='1';
        }
    }
    vector<int> ans;
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            if(graph[r][c]){
                int l = 0;
                DFS(graph,l,r,c);
                ans.push_back(l);
            }
        }
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<"\n";
    for(int i = 0; i < ans.size(); ++i)
        cout<<ans[i]<<"\n";
}