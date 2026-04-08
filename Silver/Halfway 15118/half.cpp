#include <iostream>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n;
    ll cnt = 0;
    ll s = ((n)*(n-1)/2LL)/2LL + ((n)*(n-1)/2LL)%2LL;
    for(ll i = n-1; i > 0; --i){
        cnt+=i;
        if(cnt >= s){
            cout<<(n-i)<<"\n";
            break;
        }
    }
}