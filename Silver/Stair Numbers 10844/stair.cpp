#include <iostream>
#define ll long long
using namespace std;
const ll M = ((ll)1e9);
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    ll DP[101][10];
    DP[1][0]=0;
    for(int i = 1; i <= 9; ++i)
        DP[1][i]=1;
    for(int i = 2; i <= n; ++i){
        for(int j = 0; j < 10; ++j){
            DP[i][j] = ((j==0?0:DP[i-1][j-1])%M + (j==9?0:DP[i-1][j+1])%M)%M;
        }
    }
    ll ans = 0;
    for(int i = 0; i < 10; ++i)
        ans=(ans+DP[n][i])%M;
    cout<<ans<<"\n";
}