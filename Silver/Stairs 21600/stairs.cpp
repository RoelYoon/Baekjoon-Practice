#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> nums(n);
    for(int i = 0; i <n ; ++i){
        cin>>nums[i];
    }
    int ans = 0;
    int cur = 0;
    for(int i = 0; i < n; ++i){
        if(cur < nums[i]){
            ++cur;
        }else{
            cur = nums[i];
        }
        ans = max(ans,cur);
    }
    cout<<ans<<"\n";   
}