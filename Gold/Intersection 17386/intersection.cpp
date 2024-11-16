#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define ll long long
#define pt complex<ll>
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
bool intersects(Segment a, Segment b){
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
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x1,y1,x2,y2,x3,y3,x4,y4;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    cout<<intersects(Segment({x1,y1},{x2,y2}),Segment({x3,y3},{x4,y4}))<<"\n";
}