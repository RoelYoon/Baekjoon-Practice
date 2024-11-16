#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
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
class UnionFind{
    int n;
    vector<int> rep;
    vector<int> rank;
    public:
    UnionFind(int n):n(n),rep(n),rank(n){
        for(int i = 0; i < n; ++i){
            rep[i]=i;
        }
    }
    int find(int p){
        if(rep[p]==p) return p;
        return rep[p]=find(rep[p]);
    }
    void merge(int a, int b){
        a=find(a);
        b=find(b);
        if(rank[a]>rank[b]){
            rep[b]=a;
        }else if(rank[b]>rank[a]){
            rep[a]=b;
        }else{
            rank[b]=a;
            ++rank[a];
        }
    }
    int size(){
        vector<bool> found(n);
        int cnt=0;
        for(int i = 0; i < n; ++i){
            cnt+=!found[find(i)];
            found[find(i)]=1;
        }
        return cnt;
    }
    int mxGroupSize(){
        vector<int> s(n);
        int mx=0;
        for(int i = 0; i < n; ++i){
            ++s[find(i)];
            mx=max(mx,s[find(i)]);
        }
        return mx;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Segment> segments;
    UnionFind unions(n);
    for(int i = 0; i < n; ++i){
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        segments.push_back({{x1,y1},{x2,y2}});
    }
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(intersects(segments[i],segments[j])){
                unions.merge(i,j);
            }
        }
    }
    cout<<unions.size()<<"\n"<<unions.mxGroupSize()<<"\n";
}
