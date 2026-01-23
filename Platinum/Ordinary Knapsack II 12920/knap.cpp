#include <iostream>
#include <vector>
#include <cmath>
#define ll long long
using namespace std;
struct Item{
    ll v;
    ll w;
    Item(){}
    Item(ll v, ll w):v(v),w(w){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,C; cin>>n>>C;
    vector<Item> items;
    for(int i = 0; i < n; ++i){
        int w,v,k; cin>>w>>v>>k;
        int p = (int)log2(k+1)-1;
        for(int j = 0; j <= p; ++j)
            items.push_back({(ll)v*(1<<j),(ll)w*(1<<j)});
        if((k+1)&(k))
            items.push_back({(ll)v*(k-(1<<(p+1))+1),(ll)w*(k-(1<<(p+1))+1)});
    }
    ll DP[10001]{};
    for(int i = 0; i < items.size(); ++i){
        for(int c = C; c>=1; --c){
            if(c<items[i].w) continue;
            DP[c]=max(DP[c],DP[c-items[i].w]+items[i].v);
        }
    }
    cout<<DP[C]<<"\n";
}