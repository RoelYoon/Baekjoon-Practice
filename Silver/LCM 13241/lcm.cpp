#include <iostream>
#define ll long long
using namespace std;
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b);}
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll a,b; cin>>a>>b;
    cout<<lcm(a,b)<<"\n";
}