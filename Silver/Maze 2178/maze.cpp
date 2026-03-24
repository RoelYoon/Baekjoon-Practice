#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int dirR[4]{0,1,0,-1};
const int dirC[4]{1,0,-1,0};
struct CD{
    int r,c,t;
    CD(){}
    CD(int r, int c, int t):r(r),c(c),t(t){}
};
int R,C; 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C;
    vector<string> grid(R);
    for(int r = 0; r < R; ++r){
        cin>>grid[r];
    }
    vector<vector<bool>> visited(R,vector<bool>(C));
    int ans = 0;
    queue<CD> q;
    q.emplace(0,0,0);
    visited[0][0]=1;
    while(!q.empty()){
        CD head = q.front(); q.pop();
        if(head.r==R-1 && head.c==C-1){
            ans = head.t+1;
            break;
        }
        for(int i = 0; i < 4; ++i){
            int nxtR = head.r+dirR[i];
            int nxtC = head.c+dirC[i];
            if(nxtR>=0 && nxtR<R && nxtC>=0 && nxtC<C && !visited[nxtR][nxtC] && grid[nxtR][nxtC]=='1'){
                visited[nxtR][nxtC]=1;
                q.emplace(nxtR,nxtC,head.t+1);
            }
        }
    }
    cout<<ans<<"\n";
}