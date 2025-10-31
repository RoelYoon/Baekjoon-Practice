#include <iostream>
#include <queue>
#include <vector>
#define MAX 100001
using namespace std;
inline bool inBounds(int x){
    return x>=0 && x<MAX;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    queue<int> q;
    vector<int> visited(MAX,-1);
    visited[n] = 0;
    q.push(n);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        if(cur==k){
            break;
        }
        if(inBounds(cur+1) && visited[cur+1]==-1){
            q.push(cur+1);
            visited[cur+1]=visited[cur]+1;
        }
        if(inBounds(cur-1) && visited[cur-1]==-1){
            q.push(cur-1);
            visited[cur-1]=visited[cur]+1;
        }
        if(inBounds(cur*2) && visited[cur*2]==-1){
            q.push(cur*2);
            visited[cur*2]=visited[cur]+1;
        }
    }
    cout<<visited[k]<<"\n";
}