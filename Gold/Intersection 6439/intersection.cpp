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
bool between(int a, int b, int x){
    return (a<=x && x<=b) || (b<=x && x<=a);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        vector<Segment> segments;
        int x1,y1,x2,y2; 
        cin>>x1>>y1>>x2>>y2;
        Segment line({x1,y1},{x2,y2});
        cin>>x1>>y1>>x2>>y2;
        segments.push_back({{x1,y1},{x2,y1}});
        segments.push_back({{x1,y2},{x2,y2}});
        segments.push_back({{x1,y1},{x1,y2}});
        segments.push_back({{x2,y1},{x2,y2}});
        bool it=0;
        for(int i = 0; i < 4; ++i){
            if(intersects(line,segments[i])){
                it=1;
                break;
            }
        }
        if(!it){
            it=(between(x1,x2,line.p.X) && between(y1,y2,line.p.Y))|| (between(x1,x2,line.q.X) && between(y1,y2,line.q.Y));
        }
        cout<<(it?"T":"F")<<"\n";
    }
}