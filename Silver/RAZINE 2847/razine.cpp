#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    int nums[100];
    for(int i = 0; i < n; ++i)
        cin>>nums[i];
    int cur = nums[n-1];    
    int ans = 0;
    for(int i = n-2; i >= 0; --i){
        if(nums[i] >= cur){
            ans+=(nums[i]-cur+1);
            nums[i] = cur-1;
        }
        cur = nums[i]; 
    }
    cout<<ans<<"\n";
}
