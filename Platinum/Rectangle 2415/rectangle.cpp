#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#define ll long long
#define ld long double
#define pt complex<ll> 
#define ppt complex<ld>
#define EPS 1e-12
#define X real()
#define Y imag()
using namespace std;
inline ll dot(pt a, pt b){
    return a.X*b.X+a.Y*b.Y;
}
inline ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
struct Pair{
    int p,q;
    Pair(){}
    Pair(int a, int b):p(a),q(b){}
};
inline ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
struct LinePoint{
    Pair p;
    ll length;
    ld ag;
    ppt mid;
    LinePoint(){}
    LinePoint(pt &a, pt &b, int i, int j):p(i,j),length(sq(b-a)),mid((a.X+b.X)/2.0L,(a.Y+b.Y)/2.0L),ag(arg(b-a)){}
    bool operator==(const LinePoint &a) const {
        return length==a.length && fabs(mid.X-a.mid.X)<EPS && fabs(mid.Y-a.mid.Y)<EPS && fabs(ag-a.ag)<EPS;
    }
};
pt points[1500];
ll findArea(Pair &a, Pair &b){
    pt pts[4]{points[a.p],points[a.q],points[b.p],points[b.q]};
    ppt o((points[a.p].X+points[a.q].X)/2.0L,(points[a.p].Y+points[a.q].Y)/2.0L);
    sort(pts,pts+4,[o](const pt&a, const pt&b){
        return arg(ppt(a.X-o.X,a.Y-o.Y))<arg(ppt(b.X-o.X,b.Y-o.Y));
    });
    ld area = cross(pts[3],pts[0]);
    for(int i = 0; i < 3; ++i){
        area+=cross(pts[i],pts[i+1]);
    }
    return round(fabs(area)/2);
}
bool makesRectangle(LinePoint &a, LinePoint &b){
    return fabs(a.mid.X-b.mid.X)<EPS && fabs(a.mid.Y-b.mid.Y)<EPS && (a.length==b.length);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i = 0; i <n; ++i){
        ll x,y; cin>>x>>y;
        points[i]=pt(x,y);
    }
    vector<LinePoint> lps;
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j<n; ++j){
            lps.emplace_back(points[i],points[j],i,j);
        }
    }
    ll area=0;
    sort(lps.begin(),lps.end(),[](const LinePoint &a, const LinePoint &b){
        if(fabs(a.mid.X-b.mid.X)<EPS){
            if(fabs(a.mid.Y-b.mid.Y)<EPS){
                if(a.length==b.length){
                    return a.ag<b.ag; 
                }return a.length<b.length;
            }return a.mid.Y<b.mid.Y;
        }return a.mid.X<b.mid.X;
    });
    for(int i = 0; i < lps.size(); ++i){
        int j = i+1;
        while(j<lps.size() && makesRectangle(lps[i],lps[j])){
            ++j;
        }
        --j;
        if(i==j) continue;
        for(; i<j; ++i){
            for(int k = i+1; k <= min(j,(int)lps.size()-1); ++k){
                area=max(area,findArea(lps[i].p,lps[k].p));
            }
        }
    }
    cout<<area<<"\n";
}