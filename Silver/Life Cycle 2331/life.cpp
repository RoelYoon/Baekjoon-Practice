#include <iostream>
#include <cmath>
#include <unordered_map>
#define ll long long
using namespace std;
int p;
void update(ll &num){
    ll k = num;
    num = 0;
    while(k){
        num+=pow(k%10,p);
        k/=10;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n>>p;
    int cnt = 0;
    unordered_map<ll,ll> nums{{n,0}};
    update(n);
    while(nums.find(n)==nums.end()){
        ++cnt;
        nums.insert({n,cnt});
        update(n);
    }
    cout<<(nums.find(n)->second)<<"\n";
}