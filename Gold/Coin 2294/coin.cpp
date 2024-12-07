#include <iostream>
using namespace std;
int coin[100],dp[10001]{0};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); 
    int n,k; cin>>n>>k;
    for(int i = 0; i < n; ++i)
        cin>>coin[i];
    for(int i = 1; i <= k; ++i)
        dp[i]=1e9;
    for(int i = 0; i < n; ++i)
        for(int j = coin[i]; j <= k; ++j)
            dp[j]=min(dp[j],dp[j-coin[i]]+1);
    cout<<(dp[k]==1e9?-1:dp[k])<<"\n";
}