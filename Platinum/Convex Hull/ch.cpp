#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#define X real()
#define Y imag()
#define ll long long
#define Point complex<ll>
using namespace std;
ll cross(Point &a, Point &b){
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
        if(a.X==b.X)
        return a.Y<b.Y;
        return a.X<b.X;
    });
    vector<Point> ch{points[0],points[1]};
    bool uh=1;
    int us=0;
    for(int i = 2; uh?i < n:i>=0; uh?++i:--i){
        Point v=ch[ch.size()-1]-ch[ch.size()-2];
        Point v2 = points[i]-ch[ch.size()-1];
        while(ch.size()-us>1 && cross(v,v2)>=0){
            ch.pop_back();
            if(ch.size()-us>1){
                v=ch[ch.size()-1]-ch[ch.size()-2];
                v2 = points[i]-ch[ch.size()-1];
            }
        }
        ch.push_back(points[i]);
        if(i==n-1) {uh=0; us=ch.size()-1; --i; ch.push_back(points[i]);};
    }
    ch.pop_back();
    cout<<"\n";
    for(int i = 0; i < ch.size(); ++i){
        cout<<ch[i].X<<" "<<ch[i].Y<<"\n";
    }
    cout<<ch.size()<<"\n";
}