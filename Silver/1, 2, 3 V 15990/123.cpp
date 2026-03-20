#include <iostream>
using namespace std;
const int M = ((int)1e9)+9;
int DP[100001][3];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    DP[1][0] = 1;
    DP[2][1] = 1;
    DP[3][2] = 1;
    DP[3][1] = 1;
    DP[3][0] = 1;
    for(int i = 4; i <= 100000; ++i){
        DP[i][0] = (DP[i-1][1] + DP[i-1][2])%M;
        DP[i][1] = (DP[i-2][0] + DP[i-2][2])%M;
        DP[i][2] = (DP[i-3][0] + DP[i-3][1])%M;
    }
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        cout<<((DP[n][0]+DP[n][1])%M+DP[n][2])%M<<"\n";
    }
}