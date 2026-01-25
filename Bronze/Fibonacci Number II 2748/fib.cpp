#include <iostream>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    ll DP[91];
    DP[0]=0;
    DP[1]=1;
    for(int i = 2; i <= n; ++i)
        DP[i]=DP[i-1]+DP[i-2];
    cout<<DP[n]<<"\n";
}