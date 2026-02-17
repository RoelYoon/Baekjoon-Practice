#include <iostream>
#include <vector>
using namespace std;
int n,h;
void DFS(int &ans,int i, int height, vector<int> &hs){
    if(height >= h){
        ans = min(ans,height-h);
        return;
    }
    if(i==n){
        return;
    }
    DFS(ans,i+1,height+hs[i],hs);
    DFS(ans,i+1,height,hs);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>h;
    vector<int> height(n);
    for(int i = 0; i < n; ++i)
        cin>>height[i];
    int ans = 1e9;
    DFS(ans,0,0,height);
    cout<<ans<<"\n";
}