#include <iostream>
#define INF ((int)1e9+1)
#define MAX_N 1000000
using namespace std;
int DP[MAX_N+1];
int nums[MAX_N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>nums[i];
        DP[i+1] = INF;
    }
    DP[0] = -INF;
    for(int i = 0; i < n; ++i){
        int lb = 0, rb = n;
        while(lb < rb){
            int mid = (lb+rb)/2;
            if(DP[mid] < nums[i]){
                lb = mid+1;
            }else{
                rb = mid;
            }
        }
        if(nums[i] < DP[lb]){
            DP[lb] = nums[i];
        }
    }
    int ans = 0;
    for(int i = n; i >= 1; --i){
        if(DP[i]!=INF){
            ans = i;
            break;
        }
    }
    cout<<ans<<"\n";
}