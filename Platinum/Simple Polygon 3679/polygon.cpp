#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#define X real()
#define Y imag()
#define ll long long
#define Point complex<ll>
using namespace std;
struct PointPair{
    int id;
    Point p;
    PointPair(){}
    PointPair(int x, int y, int id):p(x,y),id(id){}
};
ll cross(Point a, Point b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vector<PointPair> points;
        for(int i = 0; i < n; ++i){
            int x,y; cin>>x>>y;
            points.emplace_back(x,y,i);
        }
        sort(points.begin(),points.end(),[](const PointPair &a, const PointPair &b){
            if(a.p.X==b.p.X) return a.p.Y<b.p.Y;
            return a.p.X<b.p.X;
        });
        Point line = points.back().p-points[0].p;
        bool top = 0;
        bool bottom=0;
        bool collinear=0;
        for(int i = 1; i < n-1; ++i){
            ll c = cross(line,points[i].p-points.back().p);
            if(c>0){
                top=1;
            }else if(c<0){
                bottom=1;
            }else{
                collinear=1;
            }
        }
        bool case1=top&&bottom || !(top&&bottom)&&!collinear;
        bool case2=bottom&&collinear;
        vector<int> polygon{points[0].id};
        for(int i = 1; i < n-1; ++i){
            if(cross(line,points[i].p-points.back().p)>=(case1?0:(case2?0:1))){
                polygon.push_back(points[i].id);
            }
        }
        polygon.push_back(points.back().id);
        for(int i = n-2; i >=1 ; --i){
            if(cross(line,points[i].p-points.back().p)<(case1?0:(case2?0:1))){
                polygon.push_back(points[i].id);
            }
        }
        for(int i = 0; i < n; ++i){
            cout<<polygon[i]<<" ";
        }cout<<"\n";
    }
}