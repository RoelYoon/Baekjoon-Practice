#include <iostream>
#include <iomanip>
#include <complex>
#include <complex>
#include <vector>
#include <algorithm>
#define ll long long
#define ld long double
#define pt complex<ll>
#define ppt complex<ld>
#define X real()
#define Y imag()
#define nx(p) ((p+1)%ch.size())
#define pv(p) ((p-1+ch.size())%ch.size())
#define EPS 1e-12
using namespace std;
int n;
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(pt p){
    return sqrt((ld)sq(p));
}
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    vector<pt> pts;
    for(int i = 0; i < n; ++i){
        ll x,y; cin>>x>>y;
        pts.emplace_back(x,y);
    }
    sort(pts.begin(),pts.end(),[](const pt &a, const pt &b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    });
    vector<pt> ch{pts[0],pts[1]};
    int us=0;
    for(int i = 2; (us?i>=0:i < n); (us?--i:++i)){
        pt v1 = ch.back()-ch[ch.size()-2];
        pt v2 = pts[i]-ch.back();
        while(ch.size()-us>1 && cross(v1,v2)>=0){
            ch.pop_back();
            if(ch.size()-us>1){
                v1 = ch.back()-ch[ch.size()-2];
                v2 = pts[i]-ch.back();
            }
        }
        ch.push_back(pts[i]);
        if(i==n-1){us=ch.size()-1; ch.push_back(pts[--i]);}
    }ch.pop_back();
    ld minW = 1e9;
    int j = 0;
    vector<bool> found(ch.size());
    for(int i = 0; i < ch.size(); ++i){
        pt v = ch[nx(i)]-ch[i];
        ll c1 = cross(v,ch[j]-ch[pv(j)]);
        ll c2 = cross(v,ch[nx(j)]-ch[j]);
        while(i==j || nx(i)==j || signbit(c1)==signbit(c2)){
            j=nx(j);
            c1 = cross(v,ch[j]-ch[pv(j)]);
            c2 = cross(v,ch[nx(j)]-ch[j]);
        }
        if(found[i]) continue;
        found[i]=1;
        minW = min(minW,cross(ch[nx(i)]-ch[j],ch[i]-ch[j])/(abs(ch[nx(i)]-ch[i])));
        if(!cross(v,ch[nx(j)]-ch[j])){
            minW=min(minW,cross(ch[nx(i)]-ch[j],ch[i]-ch[j])/(abs(ch[nx(i)]-ch[i])));
            found[j]=1;
        }
    }
    cout<<fixed<<setprecision(6)<<minW<<"\n";
}