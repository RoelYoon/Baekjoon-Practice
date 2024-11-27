#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#define X real()
#define Y imag()
#define ll long long
#define ld long double
#define pt complex<ll>
#define ppt complex<ld>
#define nx(p) ((p+1)%m)
#define pv(p) ((p-1+m)%m)
using namespace std;
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(pt p){
    return sqrt(sq(p));
}
ld sq(ppt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(ppt p){
    return sqrt(sq(p));
}
struct Line{
    pt v;
    ll c;
    Line(pt p, pt q):v(q-p),c(cross(v,p)){}
};
bool intersection(Line &l1, Line &l2, ppt &out){
    ll d = cross(l1.v,l2.v);
    if(d==0) return 0;
    out = (ppt(l2.v.X,l2.v.Y)*(ld)l1.c - ppt(l1.v.X,l1.v.Y)*(ld)l2.c)/(ld)d;
    return 1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    for(int t = 1; t <= T; ++t){
        int n; cin>>n;
        vector<pt> pts;
        for(int i = 0; i < n; ++i){
            ll y; cin>>y;
            pts.emplace_back(i,y);
        }
        sort(pts.begin(),pts.end(),[](const pt&a, const pt&b){
            if(a.X==b.X) return a.Y<b.Y;
            return a.X<b.X;
        });
        vector<pt> ch{pts[0],pts[1]};
        int us = 0;
        for(int i = 2; us?i>=0:i < n; us?--i:++i){
            pt v = ch.back()-ch[ch.size()-2];
            pt v2 = pts[i]-ch.back();
            while(ch.size()-us>1 && cross(v,v2)>=0){
                ch.pop_back();
                if(ch.size()-us>1){
                    v = ch.back()-ch[ch.size()-2];
                    v2 = pts[i]-ch.back();
                }
            }
            ch.push_back(pts[i]);
            if(i==n-1){
                us=ch.size()-1;
                ch.push_back(pts[--i]);
            }
        }ch.pop_back();
        const int m = ch.size();
        if(m<3){
            cout<<"Case #"<<t<<": 0\n";
            continue;
        }
        int j = us;
        ld minW = 1e9;
        vector<bool> found(m);
        for(int i = 0; i < m; ++i){
            if(found[i]) continue;
            found[i]=1;
            pt v = ch[nx(i)]-ch[i];
            while(i==j || nx(i)==j || signbit(cross(v,ch[nx(j)]-ch[j]))==signbit(cross(v,ch[j]-ch[pv(j)])))
                j=nx(j);
            Line l1(ch[i],ch[nx(i)]);
            Line l2(ch[j],ch[j]+v);
            Line vert(pt(0,0),pt(0,1));
            ppt a,b;
            if(intersection(l1,vert,a) && intersection(l2,vert,b)){
                minW=min(minW,abs(a-b));
            }
            if(!cross(v,ch[nx(j)]-ch[j])){
                found[j]=1;
            }
        }
        cout<<"Case #"<<t<<": "<<fixed<<setprecision(9)<<minW/2.0L<<"\n";
    }
}