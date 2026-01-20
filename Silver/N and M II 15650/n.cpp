#include <iostream>
#include <vector>
using namespace std;
int n,m;
void DFS(vector<int> &s, int cur, int cnt){
    if(cnt==m){
        cout<<s[0];
        for(int i = 1; i < m; ++i)
            cout<<" "<<s[i];
        cout<<"\n";
        return;
    }
    for(int i = cur+1; i <= n; ++i){
        s.push_back(i);
        DFS(s,i,cnt+1);
        s.pop_back();
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    vector<int> s;
    DFS(s,0,0);
}