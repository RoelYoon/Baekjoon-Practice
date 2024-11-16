#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#define ll long long
#define ld long double
#define pt complex<ll>
#define ppt complex<ld>
#define X real()
#define Y imag()
using namespace std;
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
struct Segment{
    pt v;
    pt p,q;
    Segment(){}
    Segment(pt p, pt q):p(p),q(q),v(q-p){}
};
ll dot(pt a, pt b){
    return a.X*b.X + a.Y*b.Y;
}
bool onDisk(pt a, pt b, pt p){
    return dot(a-p,b-p)<=0;
}
bool onSegment(Segment &seg, pt p){
    return !cross(seg.v,p-seg.q) && onDisk(seg.p,seg.q,p);
}
int specialIntersections(Segment &a, Segment &b){
    vector<pt> intersections;
    if(onSegment(a,b.p))
        intersections.push_back(b.p);
    if(onSegment(a,b.q))
        intersections.push_back(b.q);
    if(onSegment(b,a.p))
        intersections.push_back(a.p);
    if(onSegment(b,a.q))
        intersections.push_back(a.q);
    intersections.erase(unique(intersections.begin(),intersections.end()),intersections.end());
    return intersections.size();
}
bool intersects(Segment &a, Segment &b){
    //canonical check
    ll c1 = cross(a.v,b.p-a.q);
    ll c2 = cross(a.v,b.q-a.q);
    ll c3 = cross(b.v,a.p-b.q);
    ll c4 = cross(b.v,a.q-b.q);
    if(signbit(c1)!=signbit(c2) && signbit(c3)!=signbit(c4))
        return 1;
    //non-canonical check
    return onSegment(a,b.p) || onSegment(a,b.q) || onSegment(b,a.p) || onSegment(b,a.q);
}
ppt intersection(Segment &s1, Segment &s2){
    ll x = cross(s1.v,s2.v),c1=cross(s1.v,s1.p),c2=cross(s2.v,s2.p);
    pt v = (s2.v*c1-s1.v*c2);
    return ppt((ld)v.X/x,(ld)v.Y/x);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x1,y1,x2,y2,x3,y3,x4,y4;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    Segment s1({x1,y1},{x2,y2});
    Segment s2({x3,y3},{x4,y4});
    bool is=intersects(s1,s2);
    cout<<is<<"\n";
    if(is){
        if(cross(s1.v,s2.v)){
            ppt i = intersection(s1,s2);
            cout<<setprecision(17)<<i.X<<" "<<i.Y<<"\n";
        }else if(specialIntersections(s1,s2)==1){
            pt p;
            if(s1.p==s2.p || s1.p==s2.q)
                p = s1.p;
            else if(s1.q==s2.p || s1.q==s2.q)
                p = s1.q;
            cout<<p.X<<" "<<p.Y<<"\n";
        }
    }
}