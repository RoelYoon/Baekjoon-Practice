#include <iostream>
#define ll long long
using namespace std;
const ll M = ((ll)1e9 + 7);
ll nums[3000];
ll modPow(ll a, ll b){
    ll res = 1;
    while(b){
        if(b&1){
            res = (res*a)%M;
        }
        a=(a*a)%M;
        b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i = 0; i < n; ++i)
        cin>>nums[i];
    ll ans = 0;
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            ll d = nums[j]-nums[i];
            int ds = j-i-1; // everything in between
            int lb=0,rb=i;
            while(lb<rb){
                int mid = (lb+rb)/2;
                if(nums[i]-nums[mid] <= d){
                    rb = mid;
                }else{
                    lb = mid+1;
                }
            }
            ds+=(i-rb); // everything left of i
            lb=j,rb=n-1;
            while(lb<rb){
                int mid = (lb+rb+1)/2;
                if(nums[mid]-nums[j]<d){
                    lb = mid;
                }else{
                    rb = mid-1;
                }
            }
            ds+=(rb-j); // everything right of j
            ans=(ans+modPow(2,n-2-ds))%M;
        }
    }
    cout<<ans<<"\n";
}