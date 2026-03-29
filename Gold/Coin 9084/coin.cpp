#include <iostream>
#include <vector>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
     while(t--){
        int n; cin>>n;
        vector<int> coins(n);
        for(int i = 0; i < n; ++i)
            cin>>coins[i];
        int m; cin>>m;
        ll DP[10001]{};
        DP[0]=1;
        for(int i = 0; i < n; ++i){
            for(int j = 1; j <= m; ++j){
                if(j-coins[i]<0) continue;
                DP[j]+=DP[j-coins[i]];
            }
        }
        cout<<DP[m]<<"\n";
    }
}