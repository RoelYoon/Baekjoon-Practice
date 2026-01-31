#include <iostream>
#define MAX_N 100000
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    int nums[MAX_N];
    int ans = ((int)-1e9);
    for(int i = 0; i < n; ++i){
        cin>>nums[i];
        ans = max(ans,nums[i]);
    }
    int DP[MAX_N];
    DP[0]=max(0,nums[0]);
    for(int i = 1; i < n; ++i){
        DP[i] = max(0,max(nums[i],DP[i-1]+nums[i]));
        ans = max(ans,DP[i]);
    }
    if(!ans){
        ans = ((int)-1e9);
        for(int i = 0; i < n; ++i){
            ans = max(ans,nums[i]);
        }
    }
    cout<<ans<<"\n";
}