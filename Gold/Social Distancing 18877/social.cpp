#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
int n,m;
vector<ll> grass;
bool possible(ll d){
    ll p = 0;
    int cnt = 0;
    for(int i = 0; i < grass.size(); i+=2){
        if(grass[i] > p){
            p=grass[i];
        }
        while(grass[i]<=p && p<=grass[i^1] && p <= ((ll)1e18) && cnt<n){
            ++cnt;
            p+=d;
        }
    }
    return cnt>=n;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i = 0; i < m; ++i){
        ll a,b; cin>>a>>b;
        grass.push_back(a);
        grass.push_back(b);
    }
    sort(grass.begin(),grass.end());
    ll lb=1,rb=((ll)1e18);
    while(lb<rb){
        ll mid = lb+(rb-lb+1)/2;
        if(possible(mid)){
            lb = mid;
        }else{
            rb = mid-1;
        }
    }
    cout<<lb<<"\n";
}