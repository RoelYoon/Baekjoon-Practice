#include <iostream>
#define INF ((int)1e9)
#define MAX_N 1000000
using namespace std;
int DP[MAX_N+1];
void printPath(int p[], int nums[], int a){
    if(p[a] == a){
        cout<<nums[a];
        return;
    }
    printPath(p, nums, p[a]);
    cout<<" "<<nums[a];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    int nums[MAX_N];
    for(int i = 0; i < n; ++i){
        cin>>nums[i];
        DP[i+1] = INF;
    }
    DP[0] = -INF;
    int ind[MAX_N+1];
    int p[MAX_N];
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
        if(lb==0 || DP[lb]==nums[i]) continue;
        if(nums[i] < DP[lb]){
            DP[lb] = nums[i];
            ind[lb] = i;
            p[i] = lb-1==0?i:ind[lb-1];
        }
    }
    int ans = 0;
    int e = -1;
    for(int i = 1; i <= n; ++i){
        if(DP[i]!=INF){
            ans = i;
            e = ind[i];
        }
    }
    cout<<ans<<"\n";
    printPath(p, nums, e);
    cout<<"\n";
}