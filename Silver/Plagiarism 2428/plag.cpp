#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> nums(n);
    for(int i = 0; i < n; ++i)
        cin>>nums[i];
    sort(nums.begin(),nums.end());
    long long cnt = 0;
    for(int i = 1; i < n; ++i){
        int lb = 0, rb = i-1;
        int x =ceil((double)nums[i]*0.9L);
        while(lb<rb){
            int mid = (lb+rb)/2;
            if(nums[mid] < x){
                lb = mid+1;
            }else{
                rb = mid;
            }
        }
        if(nums[lb]>=x){
            cnt+=(i-lb);
        }
    }
    cout<<cnt<<"\n";
}