#include <iostream>
#define M 10007
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    int DP[1001];
    DP[0]=1;
    DP[1]=1;
    for(int i = 2; i <= n; ++i)
        DP[i]=(DP[i-1]+DP[i-2])%M;
    cout<<DP[n]<<"\n";
}