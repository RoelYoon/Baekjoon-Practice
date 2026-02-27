#include <iostream>
#define ll long long
using namespace std;
ll DP[10001][3]{};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        DP[0][0] = 1;
        int n; cin>>n;
        for(int i = 1; i <= n; ++i){
            DP[i][0] = DP[i-1][0];
            if(i-2>=0)
            DP[i][1] = DP[i-2][0] + DP[i-2][1];
            if(i-3>=0)
            DP[i][2] = DP[i-3][0] + DP[i-3][1] + DP[i-3][2];
        }
        cout<<DP[n][0]+DP[n][1]+DP[n][2]<<"\n";
    }
}