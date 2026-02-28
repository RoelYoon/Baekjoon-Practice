#include <iostream>
#define INF ((int)1e9+1)
#define MAX_N 1000000
using namespace std;
int DP[MAX_N+1];
int ind[MAX_N+1];
int p[MAX_N];
int nums[MAX_N];
void printPath(int i){
    if(p[i] == -1){
        cout<<nums[i];
        return;
    }
    printPath(p[i]);
    cout<<" "<<nums[i];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i = 0; i < n; ++i){
        cin>>nums[i];
        DP[i+1] = INF;
    }
    DP[0] = -INF;
    ind[0] = -1;
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
            ind[lb] = i;
            p[i] = ind[lb-1];
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
    printPath(ind[ans]);
    cout<<"\n";
}