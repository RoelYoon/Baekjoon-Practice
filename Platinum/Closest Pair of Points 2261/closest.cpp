#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#define ll long long
#define pt complex<ll>
#define X real()
#define Y imag()
using namespace std;
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ll minDistR(vector<pt> &pts, int L, int R){
    if(L==R){
        return 1e18;
    }
    if(R-L+1==2){
        return sq(pts[R]-pts[L]);
    }
    int mid = (L+R)/2;
    ll d1 = minDistR(pts,L,mid);
    ll d2 = minDistR(pts,mid+1,R);
    ll d = min(d1,d2);
    vector<pt> strip;
    for(int i = L; i <= R; ++i)
        if((pts[mid]-pts[i]).X*(pts[mid]-pts[i]).X<d)
            strip.push_back(pts[i]);
    sort(strip.begin(),strip.end(),[](const pt&a, const pt&b){
        return a.Y<b.Y;
    });
    for(int i = 0; i < strip.size(); ++i)
        for(int j = i+1; j < strip.size() && (strip[j]-strip[i]).Y*(strip[j]-strip[i]).Y<d; ++j)
            d=min(d,sq(strip[j]-strip[i]));
    return d;
}
ll minDist(vector<pt> &pts){
    return minDistR(pts,0,pts.size()-1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<pt> pts;
    for(int i=0; i < n; ++i){
        int x,y; cin>>x>>y;
        pts.emplace_back(x,y);
    }
    sort(pts.begin(),pts.end(),[](const pt&a, const pt&b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    });
    cout<<minDist(pts)<<"\n";
}