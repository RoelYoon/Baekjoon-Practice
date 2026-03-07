#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    string grid[50];
    int DP[50][50];
    for(int t = 1; t <= T; ++t) {
        int ans = 0;
        int R,C; cin>>C>>R;
        for(int r = 0; r < R; ++r){
            cin>>grid[r];
            for(int c = 0; c < C; ++c){
                DP[r][c] = grid[r][c]=='R' || grid[r][c]=='T' || grid[r][c]=='W';
                if(r>0)
                DP[r][c] += DP[r-1][c];
                if(c>0)
                DP[r][c] += DP[r][c-1];
                if(r>0 && c>0)
                DP[r][c] -= DP[r-1][c-1];
            }
        }
        for(int r = 0; r < R; ++r){
            for(int c =0 ; c < C; ++c){
                for(int r2 = r; r2 < R; ++r2){
                    for(int c2 = c ; c2 < C; ++c2){
                        int area = DP[r2][c2];
                        if(r>0)
                        area-=DP[r-1][c2];
                        if(c>0)
                        area-=DP[r2][c-1];
                        if(r>0 && c>0)
                        area+=DP[r-1][c-1];
                        if(area == 0)
                        ans=max(ans,(r2-r+1) * (c2-c+1));
                    }
                }
            }
        }
        cout<<"Case #"<<t<<": "<<ans<<"\n";
    }
}