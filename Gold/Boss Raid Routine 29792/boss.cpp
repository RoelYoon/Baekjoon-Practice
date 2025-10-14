#include <iostream>
#include <unordered_map>
#include <algorithm>
#define ll long long
using namespace std;
struct Boss{
    ll health, meso;
    Boss(){}
    Boss(ll h, ll m):health(h),meso(m){}
};
struct State{
    int i;
    ll damage;
    State(){}
    State(int i, ll d):i(i),damage(d){}
    bool operator==(const State &s) const {
        return s.i==i && s.damage==damage;
    } 
    struct Hash{
        size_t operator()(const State &k) const {
            size_t h1 = hash<int>()(k.i);
            return h1^(hash<ll>()(k.damage) + 11400714819323198485ULL + (h1<<6) + (h1>>2));
        }
    };
};
unordered_map<State,ll,State::Hash> DP;
ll damage[50];
Boss bosses[13];
// max meso after processing first i bosses with d damage 
ll maxMeso(int i, ll d, ll minD){
    if(d<0) return -1e12;
    if(i<0 || d==0) return 0;
    State s(i,d);
    if(DP.count(s)) return DP[s];
    // pick current boss / no pick
    ll appliedDamage = bosses[i].health - (bosses[i].health%minD) + ((bosses[i].health%minD) ? minD : 0);
    return DP[s]=max(maxMeso(i-1,d,minD),maxMeso(i-1,d-appliedDamage,minD)+bosses[i].meso);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m,k; cin>>n>>m>>k;
    for(int i = 0; i < n; ++i){
        cin>>damage[i];
    }
    for(int i = 0; i < k; ++i){
        cin>>bosses[i].health>>bosses[i].meso;
    }
    sort(damage,damage+n,[](const ll &a, const ll &b){
        return a>b;
    });
    ll total = 0;
    // for all picked characters
    for(int i = 0; i < m; ++i){
        DP.clear();
        total+=maxMeso(k-1,900*damage[i],damage[i]);
    }
    cout<<total<<"\n";
}