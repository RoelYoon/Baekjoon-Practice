#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#define ll long long
#define pt complex<ll>
#define X real()
#define Y imag()
#define nx(p) ((p+1)%m)
#define pv(p) ((p-1+m)%m)
using namespace std;
enum Type{
    E,
    M,
    C
};
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
ll md(pt p){
    return abs(p.X)+abs(p.Y);
}
ll cd(pt p){
    return max(abs(p.X),abs(p.Y));
}
ll minDistR(vector<pt> &pts, int L, int R, Type t){
    if(L==R){
        return 1e18;
    }
    if(R-L+1==2){
        return t==E?sq(pts[R]-pts[L]):(t==M?md(pts[R]-pts[L]):cd(pts[R]-pts[L]));
    }
    int mid = (L+R)/2;
    ll d1 = minDistR(pts,L,mid,t);
    ll d2 = minDistR(pts,mid+1,R,t);
    ll d = min(d1,d2);
    vector<pt> strip;
    for(int i = L; i <= R; ++i)
        if((t==E?((pts[mid]-pts[i]).X*(pts[mid]-pts[i]).X<d):(abs((pts[mid]-pts[i]).X)<d)))
            strip.push_back(pts[i]);
    sort(strip.begin(),strip.end(),[](const pt&a, const pt&b){
        return a.Y<b.Y;
    });
    for(int i = 0; i < strip.size(); ++i)
        for(int j = i+1; j < strip.size() && (t==E?((strip[j]-strip[i]).Y*(strip[j]-strip[i]).Y<d):(abs((strip[j]-strip[i]).Y)<d)); ++j)
            d=min(d,t==E?sq(strip[j]-strip[i]):(t==M?md(strip[j]-strip[i]):cd(strip[j]-strip[i])));
    return d;
}
ll maxDist(vector<pt> &pts, vector<pt> &ch, int us, Type t){
    const int m = ch.size();
    if(m<3){
        if(m==2)
            return t==E?sq(ch[0]-ch[1]):(t==M?md(ch[0]-ch[1]):cd(ch[0]-ch[1]));
        else
            return t==E?sq(pts[0]-pts.back()):(t==M?md(pts[0]-pts.back()):cd(pts[0]-pts.back()));
        return 0;
    }
    int j = us;
    bool found[100000]{};
    ll maxD=0;
    for(int i = 0; i < m; ++i){
        if(found[i]) continue;
        found[i]=1;
        pt v = ch[nx(i)]-ch[i];
        while(i==j || nx(i)==j ||
        signbit(cross(v,ch[nx(j)]-ch[j]))==signbit(cross(v,ch[j]-ch[pv(j)])))
            j=nx(j);
        maxD=max(maxD,max(t==E?sq(ch[i]-ch[j]):(t==M?md(ch[i]-ch[j]):cd(ch[i]-ch[j])),t==E?sq(ch[nx(i)]-ch[j]):(t==M?md(ch[nx(i)]-ch[j]):cd(ch[nx(i)]-ch[j]))));
        if(!cross(v,ch[nx(j)]-ch[j])){
            maxD=max(maxD,max(t==E?sq(ch[i]-ch[nx(j)]):(t==M?md(ch[i]-ch[nx(j)]):cd(ch[i]-ch[nx(j)])),t==E?sq(ch[nx(i)]-ch[nx(j)]):(t==M?md(ch[nx(i)]-ch[nx(j)]):cd(ch[nx(i)]-ch[nx(j)]))));
            found[j]=1;
        }
    }
    return maxD;
}
ll minDist(vector<pt> &pts, Type t){
    return minDistR(pts,0,pts.size()-1, t);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<pt> pts;
    for(int i=0; i < n; ++i){
        int x,y; cin>>x>>y;
        pts.emplace_back(x,y);
    }
    sort(pts.begin(),pts.end(),[](const pt&a, const pt&b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    });
    vector<pt> ch{pts[0],pts[1]};
    ch.reserve(100000);
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
    cout<<maxDist(pts,ch,us,E)<<"\n"<<minDist(pts,E)<<"\n"<<maxDist(pts,ch,us,M)<<"\n"<<minDist(pts,M)<<"\n"<<maxDist(pts,ch,us,C)<<"\n"<<minDist(pts,C)<<"\n";
}