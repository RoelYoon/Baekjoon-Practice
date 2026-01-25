#include <iostream>
#define MAX_N 50000
#define INF ((int)1e9)
using namespace std;
int DP[MAX_N+1]{};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 0; i <= MAX_N; ++i)
        DP[i]=INF;
    int n; cin>>n;
    DP[0]=0;
    DP[1]=1;
    for(int i = 2; i <= n; ++i){
        for(int j = 1; j*j <= n && i-j*j>=0; ++j){
            DP[i]=min(DP[i],DP[i-j*j]+1);
        }
    }
    cout<<DP[n]<<"\n";
}