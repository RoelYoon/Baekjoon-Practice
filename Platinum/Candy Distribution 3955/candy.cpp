#include <iostream>
#include <vector>
#define ll long long
#define ld long double
#define MAX ((ll)1e9)
using namespace std;
struct PrimeFactor{
    ll p,a;
    PrimeFactor(){}
    PrimeFactor(ll p, ll a):p(p),a(a){}
};
ll gcd(ll a, ll b){
    return (b==0?a:gcd(b,a%b));
}
ll modpow(ll a, ll b, ll m){
    a%=m;
    ll res = 1;
    while(b){
        if(b&1){
            res=(res*a)%m;
        }
        a=(a*a)%m;
        b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        ll k,c; cin>>k>>c;
        if(gcd(k,c)!=1){
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        vector<PrimeFactor> pf;
        ll n = k;
        for(int x=2; x*x<=n; ++x){
            int cnt = 0;
            while(n%x==0){
                ++cnt;
                n/=x;
            }
            if(cnt) pf.emplace_back(x,cnt);
        }
        if(n>1) pf.emplace_back(n,1);
        ll pTotient = k;
        for(int i = 0; i < pf.size(); ++i){
            pTotient -= pTotient/pf[i].p;
        }
        ll ans = modpow(c,pTotient-1,k);
        if(ans*c < k+1)
            ans+=k;
        if(ans>MAX){
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        cout<<ans<<"\n";
    }
}