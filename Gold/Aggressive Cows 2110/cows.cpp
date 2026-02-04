#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
bool works(vector<int> &nums, int c, ll x){
    ll d = -1;
    int cnt = 0;
    for(int i = 0; i < nums.size(); ++i){
        if(d <= nums[i]){
            d = nums[i]+x;
            ++cnt;
        }
    }
    return cnt>=c;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, c; cin>>n>>c;
    vector<int> nums(n);
    for(int i = 0; i < n; ++i){
        cin>>nums[i];
    }
    sort(nums.begin(),nums.end());
    ll lb = 0, rb = ((ll)1e9);
    while(lb<rb){
        ll mid = (lb+rb+1)/2;
        if(works(nums,c,mid)) {
            lb = mid;
        } else{
            rb = mid-1;
        }
    }
    cout<<lb<<"\n";
}