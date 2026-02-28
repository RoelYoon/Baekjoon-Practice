#include <iostream>
#define ll long long
#define INF ((ll)1e18)
using namespace std;
ll DP[500][500];
ll nums[500];
class PrefixSum{
    int n;
    ll sumA[500];
    public:
    PrefixSum(int n, ll data[]):n(n){
        sumA[0]=data[0];
        for(int i = 1; i < n; ++i){
            sumA[i] = sumA[i-1]+data[i];
        }
    }
    ll sum(int L, int R){
        if(L==0) return sumA[R];
        return sumA[R]-sumA[L-1];
    }
};
ll minCost(int L, int R, PrefixSum &pf){
    if(L==R){
        return 0;
    }
    if(DP[L][R]!=INF) return DP[L][R];
    ll ans = INF;
    for(int i = L; i < R; ++i){
        ans = min(ans,minCost(L,i,pf)+minCost(i+1,R,pf)+pf.sum(L,R));
    }
    return DP[L][R] = ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        for(int i = 0; i < n; ++i){
            cin>>nums[i];
            for(int j = 0; j < n; ++j)
                DP[i][j]=INF;
        }       
        PrefixSum pf(n,nums);
        cout<<minCost(0,n-1,pf)<<"\n";
    }
}