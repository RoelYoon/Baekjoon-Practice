#include <iostream>
#define ll long long
#define MAX 100
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    ll DP[MAX+1];
    DP[1]=1;
    DP[2]=1;
    DP[3]=1;
    DP[4]=2;
    DP[5]=2;
    for(int i = 6; i <= MAX; ++i)
        DP[i]=DP[i-1]+DP[i-5];
    while(t--){
        int n; cin>>n;
        cout<<DP[n]<<"\n";
    }
}