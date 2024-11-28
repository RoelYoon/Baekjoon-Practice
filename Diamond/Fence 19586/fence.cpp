#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#define ll long long
#define ld long double
#define pt complex<ll>
#define ppt complex<ld>
#define X real()
#define Y imag()
#define nx(p) ((p+1)%m)
#define pv(p) ((p-1+m)%m)
#define EPS 1e-12
using namespace std;
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(pt p){
    return sqrt(sq(p));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<pt> pts;
    for(int i = 0; i < n; ++i){
        ll x,y; cin>>x>>y;
        pts.emplace_back(x,y);
    }
    sort(pts.begin(),pts.end(),[](const pt&a, const pt&b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    });
    vector<pt> ch{pts[0],pts[1]};
    int us=0;
    for(int i = 2; us?i>=0:i<n; us?--i:++i){
        pt v = ch.back()-ch[ch.size()-2];
        pt v2 = pts[i]-ch.back();
        while(ch.size()-us>1 && cross(v,v2)>=0){
            ch.pop_back();
            if(ch.size()-us>1){
                v= ch.back()-ch[ch.size()-2];
                v2=pts[i]-ch.back();
            }
        }
        ch.push_back(pts[i]);
        if(i==n-1){
            us=ch.size()-1;
            ch.push_back(pts[--i]);
        }
    }ch.pop_back();
    int m=ch.size();
    if(m<3){
        if(n==2){
            cout<<fixed<<setprecision(9)<<2.0L*abs(ch[0]-ch[1])<<"\n";
        }else{
            cout<<fixed<<setprecision(9)<<2.0L*abs(pts[0]-pts.back())<<"\n";
        }
        return 0;
    }
    int cur=0;
    int ap=us;
    int side=0;
    int sideAp=0;
    ld minA=1e18;
    for(; cur < m; ++cur){
        pt v = ch[nx(cur)]-ch[cur];
        while(cur==ap || nx(cur)==ap || signbit(cross(v,ch[nx(ap)]-ch[ap]))==signbit(cross(v,ch[ap]-ch[pv(ap)])))
            ap=nx(ap);
        ld height=(cross(ch[cur]-ch[ap],ch[nx(cur)]-ch[ap]))/(abs(v));
        pt perpV(v.Y,-v.X);
        while(signbit(cross(perpV,ch[nx(side)]-ch[side]))==signbit(cross(perpV,ch[side]-ch[pv(side)])))
            side=nx(side);
        bool fullEdge = !cross(perpV,(ch[nx(side)]-ch[side]));
        while(side==sideAp || (fullEdge?nx(side)==sideAp:0) || signbit(cross(perpV,ch[nx(sideAp)]-ch[sideAp]))==signbit(cross(perpV,ch[sideAp]-ch[pv(sideAp)])))
            sideAp=nx(sideAp);
        ld width=(cross(ch[side]-ch[sideAp],(ch[side]+perpV)-ch[sideAp]))/(abs(perpV));
        minA=min(minA,abs(width*2.0L)+abs(height*2.0L));
    }
    cout<<fixed<<setprecision(9)<<minA<<"\n";
}