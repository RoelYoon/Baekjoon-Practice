#include <iostream>
#include <vector>
#include <algorithm>
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
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n>>m;
    vector<pt> p1,p2;
    for(int i = 0; i < n; ++i){
        ll x,y; cin>>x>>y;
        p1.emplace_back(x,y);
    }
    for(int i = 0; i < m; ++i){
        ll x,y; cin>>x>>y;
        p2.emplace_back(x,y);
    }
    vector<pt> pts;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            pts.emplace_back(p1[i]+p2[j]);
    sort(pts.begin(),pts.end(),[](const pt&a, const pt&b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    });
    int us = 0;
    vector<pt> ch{pts[0],pts[1]};
    for(int i = 2; us?i>=0:i<pts.size(); us?--i:++i){
        pt v = ch.back()-ch[ch.size()-2];
        pt v2 = pts[i]-ch.back();
        while(ch.size()-us>1 && cross(v,v2)>=0){
            ch.pop_back();
            if(ch.size()-us>1){
                v = ch.back()-ch[ch.size()-2];
                v2 = pts[i]-ch.back();
            }
        }
        ch.push_back(pts[i]);
        if(i==pts.size()-1){
            us=ch.size()-1;
            ch.push_back(pts[--i]);
        }
    }ch.pop_back();
    reverse(ch.begin()+1,ch.end());
    cout<<ch.size()<<"\n";
    for(int i = 0; i < ch.size(); ++i){
        cout<<ch[i].X<<" "<<ch[i].Y<<"\n";
    }
}