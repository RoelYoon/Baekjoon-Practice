#include <iostream>
#define MAX_N 100000
using namespace std;
int v[2][MAX_N];
int DP[MAX_N][3];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        for(int r = 0; r < 2; ++r)
            for(int c = 0; c < n; ++c)
                cin>>v[r][c];
        DP[0][0]=v[0][0];
        DP[0][1]=v[1][0];
        DP[0][2]=0;
        for(int c = 1; c < n; ++c){
            DP[c][0] = max(DP[c-1][1] + v[0][c],DP[c-1][2] + v[0][c]);
            DP[c][1] = max(DP[c-1][0] + v[1][c],DP[c-1][2] + v[1][c]);
            DP[c][2] = max(DP[c-1][0],max(DP[c-1][1],DP[c-1][2]));
        }
        cout<<max(DP[n-1][0],max(DP[n-1][1],DP[n-1][2]))<<"\n";
    }
}