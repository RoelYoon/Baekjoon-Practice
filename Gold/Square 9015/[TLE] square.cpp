#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define ll int
#define ld long long
#define pt complex<ll> 
#define X real()
#define Y imag()
using namespace std;
inline ll dot(pt a, pt b){
    return a.X*b.X+a.Y*b.Y;
}
inline ld sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
struct Pair{
    int a,b;
    Pair(){}
    Pair(int a, int b):a(a),b(b){}
};
inline ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
pt points[3000];
unordered_map<ll,vector<Pair>> map(100000);
inline ld findArea(Pair &a, Pair &b){
    return sq(points[a.a]-points[b.a]);
}
bool intersects(Pair &a, Pair &b){
    //canonical
    pt v = points[a.b]-points[a.a];
    ll c1 = cross(v,points[b.a]-points[a.b]);
    ll c2 = cross(v,points[b.b]-points[a.b]);
    v = points[b.b]-points[b.a];
    ll c3 = cross(v,points[a.a]-points[b.b]);
    ll c4 = cross(v,points[a.b]-points[b.b]);
    return signbit(c1)!=signbit(c2) && signbit(c3)!=signbit(c4);
    //non-canonical intersection doesn't matter
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        for(int i = 0; i <n; ++i){
            int x,y; cin>>x>>y;
            points[i]=pt(x,y);
        }
        ld area=0;
        ll maxD=0;
        for(int i = 0; i < n; ++i){
            for(int j = n-1; j>=i+1; --j){
                ll d= sq(points[j]-points[i]);
                if(d<=maxD) continue;
                map[d].emplace_back(i,j);
                vector<Pair> &v = map[d];
                if(v.size()>1){
                    Pair c(i,j);
                    for(int k = 0; k < v.size()-1; ++k){
                        if(!dot(points[v[k].a]-points[i],points[v[k].b]-points[i]) && sq(points[i]-points[v[k].a])==sq(points[j]-points[v[k].b]) && sq(points[i]-points[v[k].a])==sq(points[i]-points[v[k].b]) && intersects(v[k],c)){
                            area=max(area,findArea(v[k],c));
                            cout<<area<<": "<<points[i]<<" "<<points[j]<<" "<<v[k].a<<" "<<v[k].b<<"\n";
                            map.erase(d);
                            maxD=d;
                            break;
                        }
                    }
                }
            }
        }
        cout<<area<<"\n";
        map.clear();
    }
}