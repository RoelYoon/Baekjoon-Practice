#include <iostream>
using namespace std;
int grid[50][50];
const int dirR[8]{0,1,1,1,0,-1,-1,-1};
const int dirC[8]{1,1,0,-1,-1,-1,0,1};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R,C; cin>>R>>C;
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            cin>>grid[r][c];
        }
    }
    int ans = -((int)1e9);
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            for(int i = 0; i < 8; ++i){
                int nxtR = r+dirR[i];
                int nxtC = c+dirC[i];
                if(nxtR>=0 && nxtR<R && nxtC>=0 && nxtC<C){
                    if(grid[r][c]==grid[nxtR][nxtC]){
                        ans = max(ans,grid[r][c]);
                    }
                }
            }
        }
    }
    cout<<ans<<"\n";
}