#include <iostream>
#define MAX_N 1000
#define INF ((int)1e9)
using namespace std;
int DP[MAX_N][3];
int cost[MAX_N][3];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>cost[i][0]>>cost[i][1]>>cost[i][2];
        DP[i][0]=DP[i][1]=DP[i][2]=INF;
    }
    DP[0][0]=cost[0][0];
    DP[0][1]=cost[0][1];
    DP[0][2]=cost[0][2];
    for(int i = 1; i < n; ++i){
        DP[i][0]=min(DP[i-1][1],DP[i-1][2])+cost[i][0];
        DP[i][1]=min(DP[i-1][0],DP[i-1][2])+cost[i][1];
        DP[i][2]=min(DP[i-1][0],DP[i-1][1])+cost[i][2];
    }
    cout<<min(DP[n-1][0],min(DP[n-1][1],DP[n-1][2]))<<"\n";
}