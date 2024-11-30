#include <iostream>
#define ll long long
using namespace std;
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
ll lcm(ll a,ll b){return a/gcd(a,b)* b;}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        ll a,b,c,d; cin>>a>>b>>c>>d;
        ll g = gcd(a,b);
        a/=g,b/=g;
        g=gcd(c,d);
        c/=g,d/=g;
        cout<<gcd(a,c)<<"/"<<lcm(b,d)<<" "<<lcm(a,c)<<"/"<<gcd(b,d)<<"\n";
    }
}