#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;
struct Pair{
    int i,v;
    Pair(){}
    Pair(int i, int v):i(i),v(v){}
    bool operator<(const Pair &k) const {
        if(v==k.v) return i<k.i;
        return v<k.v;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    unordered_map<int,int> i2v;
    set<Pair> pq;
    for(int i = 0; i < n; ++i){
        int v; cin>>v;
        pq.insert({i+1,v});
        i2v.insert({i+1,v});
    }
    int m; cin>>m;
    for(int i = 0; i < m; ++i){
        int t; cin>>t;
        if(t==1){
            int p,v; cin>>p>>v;
            pq.erase(Pair(p,i2v[p]));
            i2v[p]=v;
            pq.insert(Pair(p,v));
        }else{
            cout<<(pq.begin()->i)<<"\n";
        }
    }
}