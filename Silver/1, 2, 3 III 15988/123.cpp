#include <iostream>
#define ll long long
using namespace std;
const ll M = ((ll)1e9 + 9);
ll DP[1000001]{};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    DP[0] = 1;
    DP[1] = 1;
    DP[2] = 2;
    DP[3] = 4;
    for(int i = 4; i <= 1000000; ++i){
        DP[i] = ((DP[i-1] + DP[i-2])%M + DP[i-3])%M;
    }
    while(T--){
        int n; cin>>n;
        cout<<DP[n]<<"\n";
    }
}