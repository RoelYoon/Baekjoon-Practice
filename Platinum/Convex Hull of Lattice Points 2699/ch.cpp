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
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vector<Point> points;
        for(int i = 0; i < n; ++i){
            ll x,y; cin>>x>>y;
            points.emplace_back(x,y);
        }
        sort(points.begin(),points.end(),[](const Point &a, const Point &b){
            if(a.X==b.X)
                return a.Y<b.Y;
            return a.X<b.X;
        });
        vector<Point> ch{points[0],points[1]};
        int uhs=0;
        for(int i = 2; uhs?i>=0:i<n; uhs?--i:++i){
            Point v1 = ch.back()-ch[ch.size()-2];
            Point v2 = points[i]-ch.back();
            while(ch.size()-uhs>1 && cross(v1,v2)>=0){
                ch.pop_back();
                v1 = ch.back()-ch[ch.size()-2];
                v2 = points[i]-ch.back();
            }
            ch.push_back(points[i]);
            if(i==n-1){uhs=ch.size()-1; ch.push_back(points[--i]);}
        }ch.pop_back();
        cout<<ch.size()<<"\n";
        ll maxY=0;
        int j;
        for(int i = 0; i < ch.size(); ++i){
            if(ch[i].Y>maxY){
                maxY=ch[i].Y;
                j=i;
            }
        }
        for(int i = j; i < ch.size(); ++i){
            cout<<ch[i].X<<" "<<ch[i].Y<<"\n";
        }
        for(int i = 0; i < j; ++i){
            cout<<ch[i].X<<" "<<ch[i].Y<<"\n";
        }
    }
}