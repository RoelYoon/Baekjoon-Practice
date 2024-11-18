#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define ll long long
#define ld long double
#define pt complex<ll> 
#define ppt complex<ld>
#define X real()
#define Y imag()
using namespace std;
inline ll dot(pt a, pt b){
    return a.X*b.X+a.Y*b.Y;
}
inline ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
inline ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
pt points[3000];
struct Hash{
    size_t operator()(const pt&k) const {
        return hash<ll>()(k.X^33)^hash<ll>()(k.Y);
    }
};
unordered_map<pt,int,Hash> map;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        for(int i = 0; i <n; ++i){
            int x,y; cin>>x>>y;
            points[i]=pt(x,y);
            map.insert({points[i],i});
        }
        ll area=0;
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j<n; ++j){
                ll d = sq(points[j]-points[i]);
                if(d/2<=area) continue;
                pt v = points[j]-points[i];
                ppt v1 = ppt(v.X,v.Y)*polar(1.0L/sqrt(2),(ld)M_PI_4);
                ppt v2 = ppt(v.X,v.Y)*polar(1.0L/sqrt(2),(ld)-M_PI_4);
                pt p(round((ld)points[i].X+v1.X),round((ld)points[i].Y+v1.Y));
                pt q(round((ld)points[i].X+v2.X),round((ld)points[i].Y+v2.Y));
                if(sq(p-points[i])!=sq(p-points[j]) || sq(q-points[i])!=sq(q-points[j]) || dot((p-points[i]),(q-points[i])))continue;
                if(map.find(p)!=map.end() && map.find(q)!=map.end()){
                    area=d/2;
                }
            }
        }
        cout<<area<<"\n";
        map.clear();
    }
}