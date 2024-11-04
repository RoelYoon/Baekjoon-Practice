#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
#define ld long double
#define Point complex<ld>
#define X real()
#define Y imag()
using namespace std;
inline ld cross(Point &a, Point &b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Point> points;
    for(int i = 0; i < n; ++i){
        int x,y; cin>>x>>y;
        points.emplace_back(x,y);
    }
    sort(points.begin(),points.end(),[](const Point &a, const Point &b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    });
    vector<Point> ch{points[0],points[1]};
    bool uh=1;
    int uhs=0;
    for(int i = 2; uh?i < n:i>=0; uh?++i:--i){
        Point v1=ch.back()-ch[ch.size()-2];
        Point v2=points[i]-ch.back();
        while(ch.size()-uhs>1 && cross(v1,v2)>=0){
            ch.pop_back();
            if(ch.size()-uhs<2) continue;
            v1=ch.back()-ch[ch.size()-2];
            v2=points[i]-ch.back();
        }
        ch.push_back(points[i]);
        if(i==n-1){uh=0; uhs=ch.size()-1; --i; ch.push_back(points[i]);}
    }ch.pop_back();
    ld area=cross(ch.back(),ch[0]);
    for(int i = 0; i < ch.size()-1; ++i){
        area+=cross(ch[i],ch[i+1]);
    }
    cout<<(long long)(abs(area)/100)<<"\n";
}