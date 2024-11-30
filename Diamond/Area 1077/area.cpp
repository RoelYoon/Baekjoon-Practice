#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#define ll long long
#define ld long double
#define pt complex<ll>
#define ppt complex<ld>
#define X real()
#define Y imag()
#define INF 1e9
#define EPS 1e-12
using namespace std;
ld cross(ppt a, ppt b){
    return (conj(a)*b).Y;
}
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
ll dot(pt a, pt b){
    return a.X*b.X + a.Y*b.Y;
}
struct Segment{
    pt p,q;
    Segment(){}
    Segment(pt p, pt q):p(p),q(q){}
};
struct Line{
    ll c;
    pt v;
    Line(Segment &s):v(s.q-s.p){
        c=cross(v,s.p);
    };
};
bool inDisk(Segment &s, pt p){
    return dot(s.p-p,s.q-p)<=0;
}
bool onSegment(Segment &s, pt p){
    return !cross(p-s.p,p-s.q) && inDisk(s,p);
}
bool intersects(Segment &a, Segment &b){
    pt v=a.q-a.p;
    ll c1 = cross(v,b.p-a.q);
    ll c2 = cross(v,b.q-a.q);
    v=b.q-b.p;
    ll c3 = cross(v,a.p-b.q);
    ll c4 = cross(v,a.q-b.q);
    if(signbit(c1)!=signbit(c2) && signbit(c3)!=signbit(c4))
        return 1;
    if(c1>=0!=c2>=0){
        if(onSegment(a,b.p)) return 1;
        if(onSegment(a,b.q)) return 1;
    }
    return 0;
}
ppt convert(pt p){
    return ppt(p.X,p.Y);
}
ppt intersection(Line &l1, Line &l2){
    return (convert(l2.v)*(ld)l1.c-convert(l1.v)*(ld)l2.c)/(ld)cross(l1.v,l2.v);
}
ppt intersection(Segment &a, Segment &b){
    Line l1(a),l2(b);
    return intersection(l1,l2);
}
bool inPolygon(vector<pt> &polygon, pt p){
    int n = polygon.size();
    int ints = 0;
    Segment a(p,pt(INF,p.Y));
    for(int i = 0; i < n; ++i){
        Segment b(polygon[i],polygon[(i+1)%n]);
        ints+=intersects(a,b);
    }
    return ints>0 && (ints%2);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n>>m;
    vector<pt> p1,p2;
    for(int i = 0; i < n; ++i){
        ll x,y; cin>>x>>y;
        p1.emplace_back(x,y);
    }
    for(int i = 0; i < m; ++i){
        ll x,y; cin>>x>>y;
        p2.emplace_back(x,y);
    }
    vector<ppt> pts;
    ppt lowest(0,INF);
    for(int i = 0; i < n; ++i){
        if(inPolygon(p2,p1[i])){
            pts.push_back(convert(p1[i]));
            if(pts.back().Y<lowest.Y)
                lowest=pts.back();
        }
        for(int j = 0; j < m; ++j){
            Segment a(p1[i],p1[(i+1)%n]), b(p2[j],p2[(j+1)%m]);
            if(intersects(a,b)){
                pts.push_back(intersection(a,b));
                if(pts.back().Y<lowest.Y)
                    lowest=pts.back();
            }
        }
    }
    for(int i = 0; i < m; ++i){
        if(inPolygon(p1,p2[i])){
            pts.push_back(convert(p2[i]));
            if(pts.back().Y<lowest.Y)
                lowest=pts.back();
        }
    }
    if(pts.size()<3){cout<<"0\n"; return 0;}
    sort(pts.begin(),pts.end(),[](const ppt&a, const ppt&b){
        if(fabs(a.X-b.X)<EPS) return a.Y<b.Y;
        return a.X<b.X;
    });
    vector<ppt> ch{pts[0],pts[1]};
    int us = 0;
    for(int i = 2; us?i>=0:i<pts.size(); us?--i:++i){
        ppt v = ch.back()-ch[ch.size()-2];
        ppt v2 = pts[i]-ch.back();
        while(ch.size()-us>1 && (cross(v,v2)>0 || fabs(cross(v,v2))<EPS)){
            ch.pop_back();
            if(ch.size()-us>1){
                v = ch.back()-ch[ch.size()-2];
                v2 = pts[i]-ch.back();
            }
        }
        ch.push_back(pts[i]);
        if(i==pts.size()-1){
            us=ch.size()-1;
            ch.push_back(pts[--i]);
        }
    }ch.pop_back();
    if(ch.size()<3){cout<<"0\n";return 0;}
    ld area=cross(ch.back(),ch[0]);
    for(int i = 0; i < ch.size()-1; ++i)
        area+=cross(ch[i],ch[i+1]);
    cout<<fixed<<setprecision(12)<<fabs(area)/2.0L<<"\n";
}
/*
(-1,0)
(-0.333333,-2)
(0.5,-2)
(1,-1)
(1.6,0.8)
(1.25,1.5)
*/