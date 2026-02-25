#include <iostream>
#define ll long long
using namespace std;
const ll M = 10007;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll DP[1001][10]{};
    int n; cin>>n;
    for(int i = 0; i < 10; ++i){
        DP[1][i] = 1;
    }
    for(int i = 2; i <= n; ++i){
        for(int j = 0; j < 10; ++j){
            for(int k = 0; k <= j; ++k){
                DP[i][j] = (DP[i][j] + DP[i-1][k])%M;
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < 10; ++i)
        ans = (ans+DP[n][i])%M;
    cout<<ans<<"\n";
}