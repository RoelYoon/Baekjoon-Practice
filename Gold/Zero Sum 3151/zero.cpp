#include <iostream>
#include <vector>
#include <algorithm>
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
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            int lb=0,rb=n-1;
            int x = nums[i]+nums[j];
            while(lb<rb){
                int mid = (lb+rb)/2;
                if(nums[mid] < -x){
                    lb = mid+1;
                }else{
                    rb = mid;
                }
            }
            int LB=lb;
            lb=0,rb=n-1;
            while(lb<rb){
                int mid = (lb+rb+1)/2;
                if(nums[mid] <= -x){
                    lb = mid;
                }else{
                    rb = mid-1;
                }
            }
            if(nums[lb]+x==0){
                cnt += rb-LB+1;
                cnt -= (LB<=i && i<=rb);
                cnt -= (LB<=j && j<=rb);
            }
        }
    }
    cout<<cnt/3<<"\n";
}