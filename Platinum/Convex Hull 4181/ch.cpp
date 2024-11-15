#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#define ll long long
#define Point complex<ll>
#define X real()
#define Y imag()
using namespace std;
ll cross(Point a, Point b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Point> points;
    for(int i = 0; i < n; ++i){
        ll x,y; char s; cin>>x>>y>>s;
        if(s=='Y')
            points.emplace_back(x,y);
    }
    n=points.size();
    sort(points.begin(),points.end(),[](const Point &a, const Point &b){
        if(a.X==b.X)
            return a.Y<b.Y;
        return a.X<b.X;
    });
    bool uh=1;
    int us=0;
    vector<Point> ch{points[0],points[1]};
    for(int i = 2; uh?i<n:i>=0;uh?++i:--i){
        Point v1 = ch.back()-ch[ch.size()-2];
        Point v2 = points[i]-ch.back();
        while(ch.size()-us>1&&cross(v1,v2)<0){
            ch.pop_back();
            v1 = ch.back()-ch[ch.size()-2];
            v2 = points[i]-ch.back();
        }
        ch.push_back(points[i]);
        if(i==n-1){us=ch.size()-1;uh=0;ch.push_back(points[--i]);}
    }ch.pop_back();
    cout<<ch.size()<<"\n";
    for(int i = 0; i<n; ++i){
        cout<<ch[i].X<<" "<<ch[i].Y<<"\n";
    }
}