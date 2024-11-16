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
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Segment> segments; 
    for(int i = 0; i < n; ++i){
        int y; cin>>y;
        segments.push_back({{i,0},{i,y}});
    }
    int mxSee=min(2,n-1);
    for(int i = 0; i < n; ++i){
        int see = 0;
        for(int j = 0; j < n; ++j){
            if(i==j) continue;
            Segment sight(segments[i].q,segments[j].q);
            bool visible=1;
            for(int k = 0; k<n; ++k){
                if(k==i || k==j) continue;
                if(intersects(sight,segments[k])){
                    visible=0;
                    break;
                }
            }
            see+=visible;
        }
        mxSee=max(mxSee,see);
    }
    cout<<mxSee<<"\n";
}