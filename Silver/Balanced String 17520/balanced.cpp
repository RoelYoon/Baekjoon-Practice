#include <iostream>
#define ll long long
using namespace std;
ll DP[100001][2]{}; // DP[n][l][s] = number of length n, last character l, s diff
const int M = 16769023;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    DP[1][0] = DP[1][1] = 1;  
    int n; cin>>n;
    for(int i = 2; i <= n; ++i){
        if(i%2){
            DP[i][0] = (DP[i-1][1] + DP[i-1][0])%M;
            DP[i][1] = (DP[i-1][1] + DP[i-1][0])%M;
        }else{
            DP[i][0] = DP[i-1][1];
            DP[i][1] = DP[i-1][0];
        }
    }
    cout<<(DP[n][0]+DP[n][1])%M<<"\n";
}