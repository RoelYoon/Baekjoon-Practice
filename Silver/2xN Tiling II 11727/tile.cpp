#include <iostream>
using namespace std;
const int M = 10007;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    int DP[1001]{};
    DP[1]=1;
    DP[2]=3;
    for(int i = 3; i <= n; ++i){
        DP[i] = ((DP[i-2])*2 + DP[i-1])%M;
    }
    cout<<DP[n]<<"\n";
}