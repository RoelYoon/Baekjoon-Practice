#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> DP(n+1);
    DP[0] = 0;
    DP[2] = 1;
    DP[5] = 1;
    DP[4] = 2;
    for(int i = 6; i <= n; ++i){
        if(DP[i-2] != 0){
            DP[i] = DP[i-2]+1;
        }
        if(DP[i-5] != 0){
            DP[i] = min(DP[i], DP[i-5]+1);
        }
    }
    cout<<(DP[n]==0 ? -1 : DP[n])<<"\n";
}