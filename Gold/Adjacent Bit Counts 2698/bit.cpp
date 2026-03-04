#include <iostream>
#define ll long long
using namespace std;
ll DP[101][101][2]; // DP[n][k][b]
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    DP[2][0][0] = 2;
    DP[2][0][1] = 1;
    DP[2][1][1] = 1;
    for(int i = 3; i <= 100; ++i){
        for(int k = 0; k <= 100; ++k){
            DP[i][k][0] = DP[i-1][k][0] + DP[i-1][k][1];
            DP[i][k][1] = DP[i-1][k][0] + (k>0?DP[i-1][k-1][1]:0);
        }
    }
    int t; cin>>t;
    while(t--){
        int n,k; cin>>n>>k;
        cout<<DP[n][k][0]+DP[n][k][1]<<"\n";
    }
}