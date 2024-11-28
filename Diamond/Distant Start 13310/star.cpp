#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#define ll long long
#define pt complex<ll>
#define X real()
#define Y imag()
#define nx(p) ((p+1)%m)
#define pv(p) ((p-1+m)%m)
using namespace std;
struct Star{
    pt origin;
    pt dir;
    Star(){}
    Star(pt o, pt d):origin(o),dir(d){}
    pt pos(ll t) const {
        return origin+dir*t;
    }
};
int n;
vector<Star> stars;
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
ll maxDist(ll t){
    sort(stars.begin(),stars.end(),[t](const Star&a, const Star&b){
        pt ap = a.pos(t), bp=b.pos(t);
        if(ap.X==bp.X) return ap.Y<bp.Y;
        return ap.X<bp.X;       
    });
    vector<pt> ch{stars[0].pos(t),stars[1].pos(t)};
    int us = 0;
    for(int i = 0; us?i>=0:i < n; us?--i:++i){
        pt v = ch.back()-ch[ch.size()-2];
        pt v2 = stars[i].pos(t)-ch.back();
        while(ch.size()-us>1 && cross(v,v2)>=0){
            ch.pop_back();
            if(ch.size()-us>1){
                v = ch.back()-ch[ch.size()-2];
                v2 = stars[i].pos(t)-ch.back();
            }
        }
        ch.push_back(stars[i].pos(t));
        if(i==n-1){
            us=ch.size()-1;
            ch.push_back(stars[--i].pos(t));
        }
    }ch.pop_back();
    int m = ch.size();
    if(m<3){
        if(m==2)
            return sq(ch[0]-ch[1]);
        else
            return sq(stars[0].pos(t)-stars.back().pos(t));
    }
    int j=us;
    ll maxD=0;
    vector<bool> vis(m);
    for(int i = 0; i < m; ++i){
        if(vis[i]) continue;
        vis[i]=1;
        pt v = ch[nx(i)]-ch[i];
        while(i==j || nx(i)==j || signbit(cross(v,ch[nx(j)]-ch[j]))==signbit(cross(v,ch[j]-ch[pv(j)])))
            j=nx(j);
        maxD=max(maxD,max(sq(ch[i]-ch[j]),sq(ch[nx(i)]-ch[j])));
        if(!cross(v,ch[nx(j)]-ch[j])){
            maxD=max(maxD,max(sq(ch[i]-ch[nx(j)]),sq(ch[nx(i)]-ch[nx(j)])));
            vis[j]=1;
        }
    }
    return maxD;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>n>>T;
    for(int i = 0; i < n; ++i){
        int x,y,dx,dy; cin>>x>>y>>dx>>dy;
        stars.push_back({{x,y},{dx,dy}});
    }
    ll L=0,R=T;
    while(L<R){
        ll m1 = L+(R-L)/3;
        ll m2 = R-(R-L)/3;
        if(maxDist(m1)>maxDist(m2))
            L=m1+1;
        else
            R=m2-1;
    }
    cout<<L<<"\n"<<maxDist(L)<<"\n";
}