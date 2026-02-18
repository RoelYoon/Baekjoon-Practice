#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int dirR[8]{0,1,1,1,0,-1,-1,-1};
const int dirC[8]{1,1,0,-1,-1,-1,0,1};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<string> grid(8);
    for(int r = 0; r < 8; ++r){
        cin>>grid[r];
    }
    int ans = 0;
    for(int r = 0; r < 8; ++r){
        for(int c = 0; c < 8; ++c){
            if(grid[r][c]!='.') continue;
            int score=0;
            for(int i = 0; i < 8; ++i){
                int dr = r+dirR[i];
                int dc = c+dirC[i];
                int cnt = 0;
                while(dr>=0 && dr<8 && dc>=0 && dc<8 && grid[dr][dc]=='W'){
                    dr+=dirR[i];
                    dc+=dirC[i];
                    ++cnt;
                }
                if(dr>=0 && dr<8 && dc>=0 && dc<8 && grid[dr][dc]=='B')
                    score+=cnt;
            }       
            ans = max(ans,score);
        }
    }
    cout<<ans<<"\n";
}
