#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> nums(n);
    for(int i = 0; i < n; ++i){
        cin>>nums[i];
    }
    int MR = -1;
    int LR = -1;
    int LRI = -1;
    int f = -1, s = -1;
    int fc = 0, sc = 0;
    int ans = 0;
    for(int i = 0; i < n; ++i){
        if(nums[i] == f){
            ++fc;
        }else if(nums[i] == s){
            ++sc;
        }else{
            if(MR==f){
                // replace s;
                s = nums[i];
                sc = 1;
                fc = i-1 - LRI;
            }else{
                // replace f
                f = nums[i];
                fc = 1;
                sc = i-1 - LRI;
            } 
       }
        if(nums[i] != MR){
            LR = MR;
            LRI = i-1;
        }
       MR = nums[i];
       ans = max(ans, fc+sc);
    }
    cout<<ans<<"\n";
}