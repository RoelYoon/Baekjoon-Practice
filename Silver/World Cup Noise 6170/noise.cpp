#include <iostream>
#define ll long long
using namespace std;
ll DP[46][2];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    DP[1][0] = 1;
    DP[1][1] = 1;
    for(int i = 2; i <= 45; ++i){
        DP[i][0] = DP[i-1][0] + DP[i-1][1];
        DP[i][1] = DP[i-1][0];
    }
    for(int i = 0; i < t; ++i){
        int n; cin>>n;
        cout<<"Scenario #"<<i+1<<":\n"<<DP[n][0]+DP[n][1]<<"\n";
        if(i==t-1) break;
        cout<<"\n";
    }
}