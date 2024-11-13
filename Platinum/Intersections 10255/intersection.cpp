#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
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
ll dot(Point a, Point b){
    return a.X*b.X + a.Y*b.Y;
}
bool inDisk(Point a, Point b, Point p){
    return dot(a-p,b-p)<=0;
}
ll cross(Point a, Point b){
    return (conj(a)*b).Y;
}
bool onSegment(Segment &line, Point p){
    return cross(line.p2-line.p1,line.p2-p)==0 && inDisk(line.p1,line.p2,p);
}
int intersections(Segment &side, Segment &line){
    Point v = line.p2-line.p1;
    int c1 = cross(v,side.p1-line.p2);
    int c2 = cross(v,side.p2-line.p2);
    v = side.p2-side.p1;
    int c3 = cross(v,line.p1-side.p2);
    int c4 = cross(v,line.p2-side.p2);
    if(c1&&c2&&c3&&c4&&signbit(c1)!=signbit(c2) && signbit(c3)!=signbit(c4))
        return 1;
    //no proper intersection
    vector<Point> intSet;
    bool sideVertex=0;
    if(onSegment(line,side.p1)) intSet.push_back(side.p1),sideVertex=1;
    if(onSegment(line,side.p2)) intSet.push_back(side.p2),sideVertex=1;
    if(onSegment(side,line.p1)) intSet.push_back(line.p1);
    if(onSegment(side,line.p2)) intSet.push_back(line.p2);
    sort(intSet.begin(),intSet.end(),[](const Point &a, const Point &b){
        if(a.X==b.X)
            return a.Y<b.Y;
        return a.X<b.X;
    });
    intSet.erase(unique(intSet.begin(),intSet.end()),intSet.end());
    if(intSet.size()==2) return 4;
    else return intSet.size()&(sideVertex?!cross(Point(1,0),side.p2-side.p1):1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        vector<Segment> segments;
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        segments.emplace_back(x1,y1,x1,y2);
        segments.emplace_back(x1,y1,x2,y1);
        segments.emplace_back(x1,y2,x2,y2);
        segments.emplace_back(x2,y1,x2,y2);
        cin>>x1>>y1>>x2>>y2;
        if(x1>x2 || x1==x2 && y1>y2){
            int c = x1;
            x1 = x2;
            x2 = c;
            c = y1;
            y1 = y2;
            y2 = c;
        }
        Segment line(x1,y1,x2,y2);
        int n = 0;
        for(int i = 0; i < 4; ++i)
            n+=intersections(segments[i],line);
        cout<<(n>=4?4:n)<<"\n";
    }
}