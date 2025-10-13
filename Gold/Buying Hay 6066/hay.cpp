#include <iostream>
#define ll long long
#define MAXH 50001
using namespace std;
int n, H;
int hay[101]; // how much hay farmer i sells
ll cost[101]; // how much farmer i costs
// min cost of buying h hay from i first farmers
ll DP[101][50001];
ll minCost(int i, int h){
    if(h<=0) return 0;
    if(i<=0){
        // last guy
        return 1e9;
    }
    if(DP[i][h]!=-1) return DP[i][h];
    return DP[i][h]=min(minCost(i-1,h),minCost(i,h-hay[i])+cost[i]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>H;
    for(int i = 1; i <= n; ++i){
        cin>>hay[i]>>cost[i];
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= H; ++j){
            DP[i][j]=-1;
        }
    }
    cout<<minCost(n,H)<<"\n";
}