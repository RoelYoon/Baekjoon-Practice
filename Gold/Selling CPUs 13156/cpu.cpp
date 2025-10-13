#include <iostream>
#define ll long long
using namespace std;
int c,m;
int prices[105][105];
ll DP[105][105];
// maxValue obtained from going through first i merchants with $cpus number of cpus 
ll maxValue(int i, int cpus){ 
    if(i<0 || cpus<=0){
        return 0;
    }
    if(DP[i][cpus]!=-1){
        return DP[i][cpus];
    }
    ll v1 = maxValue(i-1,cpus);
    ll v2 = 0;
    for(int j = 1; j <= cpus; ++j){
        v2 = max(v2,maxValue(i-1, cpus-j) + prices[i][j]);
    }
    return DP[i][cpus]=max(v1,v2);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>c>>m;
    for(int i = 0; i < m; ++i){
        for(int j = 1; j <= c; ++j){
            DP[i][j]=-1;
        }
    }
    for(int i = 0; i < m; ++i){
        for(int j = 1; j <= c; ++j){
            cin>>prices[i][j];
        }
    }
    cout<<maxValue(m-1,c)<<"\n";
}