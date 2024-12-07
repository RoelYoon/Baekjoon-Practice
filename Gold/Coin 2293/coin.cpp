#include <iostream>
#include <map>
using namespace std;
int coin[100],dp[10001]{1};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); 
    int n,k; cin>>n>>k;
    for(int i = 0; i < n; ++i)
        cin>>coin[i];
    for(int i = 0; i < n; ++i)
        for(int j = coin[i]; j <= k; ++j)
            dp[j]+=dp[j-coin[i]];
    cout<<dp[k]<<"\n";
}