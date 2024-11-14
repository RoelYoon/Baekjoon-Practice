#include <iostream>
#include <cmath>
#include <complex>
#include <vector>
#define ll long long
#define Point complex<ll>
#define X real()
#define Y imag()
using namespace std;
struct Segment{
    Point p1,p2;
    Segment(){}
    Segment(int x1, int y1, int x2, int y2):p1(x1,y1),p2(x2,y2){}
};
struct Rectangle{
    Segment segments[4];
    Point p1,p2;
    Rectangle(){}
    void build(int x1, int y1, int x2, int y2){
        segments[0]=Segment(x1,y1,x1,y2);
        segments[1]=Segment(x1,y1,x2,y1);
        segments[2]=Segment(x1,y2,x2,y2);
        segments[3]=Segment(x2,y1,x2,y2);
        p1=Point(x1,y1);
        p2=Point(x2,y2);
    }
};
struct UnionFind{
    int n;
    vector<int> rep;
    vector<int> rank;
    UnionFind(int n):n(n),rep(n),rank(n){
        for(int i = 0; i < n; ++i)
            rep[i]=i;
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
        }else if(rank[a]<rank[b]){
            rep[a]=b;
        }else{
            rep[b]=a;
            ++rank[a];
        }
    }
    int size(){
        int s = 0;
        vector<bool> set(n);
        for(int i = 0; i < n; ++i){
            s+=!set[find(i)];
            set[rep[i]]=1;
        }
        return s;
    }
};
ll cross(Point a, Point b){
    return (conj(a)*b).Y;
}
ll dot(Point a, Point b){
    return a.X*b.X+a.Y*b.Y;
}
bool inDisk(Point a, Segment &b){
    return dot(b.p1-a,b.p2-a)<=0;
}
bool onSegment(Point a, Segment &b){
    return inDisk(a,b) && !cross(b.p2-b.p1,b.p2-a);
}
bool intersect(Segment &a, Segment &b){
    //canonical
    Point v = a.p2-a.p1;
    ll c1 = cross(v,b.p1-a.p2);
    ll c2 = cross(v,b.p2-a.p2);
    v = b.p2-b.p1;
    ll c3 = cross(v,a.p1-b.p2);
    ll c4 = cross(v,a.p2-b.p2);
    if(signbit(c1)!=signbit(c2) && signbit(c3)!=signbit(c4)) return 1;
    //noncanonical
    if(onSegment(a.p1,b) || onSegment(a.p2,b) || onSegment(b.p1,a) || onSegment(b.p2,a)) return 1;
    return 0;
}
bool intersect(Point a, Rectangle &b){
    for(int i = 0; i < 4; ++i)
        if(onSegment(a,b.segments[i]))
            return 1;
    return 0;
}
bool intersect(Rectangle &a, Rectangle &b){
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            if(intersect(a.segments[i],b.segments[j]))
                return 1;
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Rectangle> rectangles(n);
    UnionFind unions(n);
    for(int i = 0; i < n; ++i){
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        rectangles[i].build(x1,y1,x2,y2);
    }
    bool originIntersect=0;
    for(int i = 0; i < n; ++i){
        if(!originIntersect){originIntersect=intersect(Point(0,0),rectangles[i]);}
        for(int j = i+1; j < n; ++j)
            if(intersect(rectangles[i],rectangles[j]))
                unions.merge(i,j);
    }
    cout<<unions.size()-originIntersect<<"\n";
}