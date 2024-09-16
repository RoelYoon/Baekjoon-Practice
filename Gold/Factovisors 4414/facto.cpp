#include <iostream>
#include <vector>
#include <bitset>
#define MAX 100005
#define ll long long
using namespace std;
vector<int> p;
void sieve(){
    bitset<MAX> bs;
    bs.set();
    for(int i = 2; i < MAX; ++i){
        if(bs[i]){
            p.push_back(i);
            for(ll j = (ll)i*(ll)i; j < MAX; j+=i) bs[j]=0;
        }
    }
}
bool divide(ll m, ll n){
    ll mFact[MAX]{};
    ll nFact[MAX]{};
    for(int i = 0; i < p.size() && (ll)p[i] * (ll)p[i] <=m; ++i){
        while(m % p[i] == 0){
            m/=p[i];
            ++mFact[p[i]];
        }
        ll pi = (ll)p[i];
        while(n >= pi){
            nFact[p[i]]+=n/pi;
            pi*=p[i];
        }
        if(mFact[p[i]] > nFact[p[i]]) return false;
    }
    return !(m!=1 && m>n);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m; 
    sieve();
    bool n0 = 0,m0=0;
    while(cin>>n>>m){
        n0 = n==0;
        m0 = m==0;
        if(n0) n = 1;
        if(m0){
            cout<<"0 does not divide "<<n<<"!\n";
            continue;
        }
        cout<<m<<(divide(m,n) ?  " divides " : " does not divide ")<<(n0?0:n)<<"!\n";
    }
}