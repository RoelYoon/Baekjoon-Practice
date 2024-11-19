#include <iostream>
using namespace std;
long long dp[101]{0,9,1,7,4,2,6,8};
int s[8]{0,0,1,7,4,2,0,8};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 8; i < 101; ++i)
        dp[i]=1e18;
	for (int i=8; i<101; ++i) 
		for (int j=2; j<8; ++j)
			dp[i]=min(dp[i], dp[i-j]*10+s[j]);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        cout<<dp[n]<<" "<<(n%2?"7":"1")+string((n%2?n-1:n)/2 - 1,'1')+"\n";
    }
}