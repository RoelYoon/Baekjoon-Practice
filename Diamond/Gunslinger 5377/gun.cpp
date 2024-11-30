#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
#define ll long long
#define ld long double
#define pt complex<ll>
#define X real()
#define Y imag()
#define nx(p) ((p+1)%m)
#define pv(p) ((p-1+m)%m)
using namespace std;
struct Segment{
    pt p,q;
    Segment(){}
    Segment(pt p, pt q):p(p),q(q){}  
};
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(pt p){
    return sqrt(sq(p));
}
ll dot(pt a, pt b){
    return a.X*b.X + a.Y*b.Y;
}
bool inDisk(Segment &s, pt p){
    return dot(s.p-p,s.q-p)<=0;
}
bool onSegment(Segment &s, pt p){
    return !cross(p-s.p,p-s.q) && inDisk(s,p);
}
bool intersects(Segment &a, Segment &b, bool noncanonical=0){
    pt v = a.q-a.p;
    ll c1 = cross(v,b.p-a.q);
    ll c2 = cross(v,b.q-a.q);
    v = b.q-b.p;
    ll c3 = cross(v,a.p-b.q);
    ll c4 = cross(v,a.q-b.q);
    if(signbit(c1)!=signbit(c2) && signbit(c3)!=signbit(c4))
        return 1;
    // non-canonical intersections
    if(noncanonical){
        if(c1>=0 != c2>=0){
            if(onSegment(a,b.p)) return 1;
            if(onSegment(a,b.q)) return 1;
        }
    }
    return 0;
}
bool reachable(pt start, pt end, vector<pt> &obstacle){
    int m = obstacle.size();
    Segment s(start,end);
    int ints = 0;
    for(int i = 0; i < (m==2?1:m); ++i){
        Segment os(obstacle[i],obstacle[nx(i)]);
        if(m!=2&&!((cross(s.q-s.p,os.q-s.q)>=0)!=(cross(s.q-s.p,obstacle[pv(i)]-s.q)>=0))) continue;
        if(intersects(s,os) && (s.p!=os.p && s.p!=os.q)){
            ++ints;
        }else if((s.p!=os.p && s.p!=os.q && s.q!=os.p && s.q!=os.q)){
            ints+=intersects(s,os,1);
        }
    }
    return (ints==0);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    //freopen("G.in","r",stdin);
    //freopen("OUT","w",stdout);
    int t; cin>>t;
    int cnt = 0;
    while(t--){
        cnt++;
        int x,y; cin>>x>>y;
        pt start(x,y);
        cin>>x>>y;
        pt end(x,y);
        int n; cin>>n;
        vector<pt> pts;
        for(int i = 0; i < n; ++i){
            cin>>x>>y;
            pts.emplace_back(x,y);
        }
        sort(pts.begin(),pts.end(),[](const pt&a, const pt&b){
            if(a.X==b.X) return a.Y<b.Y;
            return a.X<b.X;
        });
        vector<pt> ch{pts[0],pts[1]};
        int us = 0;
        for(int i = 2; us?i>=0:i<n; us?--i:++i){
            while(ch.size()-us>1 && cross(ch.back()-ch[ch.size()-2],pts[i]-ch.back())>=0)
                ch.pop_back();
            ch.push_back(pts[i]);
            if(i==n-1){
                us=ch.size()-1;
                ch.push_back(pts[--i]);
            }
        }if(ch.size()>3)ch.pop_back();
        if(ch.size()>3 && !reachable(start,pt(100000,0),ch) && !reachable(start,pt(0,-100000),ch) && !reachable(start,pt(-100000,0),ch) && !reachable(start,pt(0,100000),ch)){
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        if(reachable(start,end,ch)){
            cout<<fixed<<setprecision(3)<<(round(abs(end-start)*1000.0L)/1000.0L)<<"\n";
            continue;
        }
        vector<int> validStart;
        vector<int> validEnd;
        int m = ch.size();
        if(m==2){
            for(int i = 0; i < ch.size(); ++i){
                validStart.push_back(i);
                validEnd.push_back(i);
            }
        }else{
            for(int i = 0; i < m; ++i){
                if(reachable(start,ch[i],ch)){
                    validStart.push_back(i);
                }
                if(reachable(ch[i],end,ch)){
                    validEnd.push_back(i);
                }
            }
        }
        if(validStart.empty() || validEnd.empty()){
            cout<<"IMPOSSIBLE\n";
            continue;
        }
        ld minDist=1e18;
        for(int i = 0; i < validStart.size(); ++i){
            ld dist = abs(ch[validStart[i]]-start);
            for(int j = 0; j < validEnd.size(); ++j){
                ld d1=dist+abs(end-ch[validEnd[j]]),d2=d1;
                int k = validStart[i];
                while(k!=validEnd[j]){
                    d1+=abs(ch[nx(k)]-ch[k]);
                    k=nx(k);
                }
                k = validStart[i];
                while(k!=validEnd[j]){
                    d2+=abs(ch[pv(k)]-ch[k]);
                    k=pv(k);
                }
                minDist=min(minDist,min(d1,d2));
            }
        }
        cout<<fixed<<setprecision(3)<<(round(minDist*1000.0L)/1000.0L)<<"\n";
    }
}
/*
1
0 0
2 0
2
1 1
1 -2

1
0 0
2 0
3
1 1
1 -2
-1 0

1
0 0
3 3
4
1 1
1 2
2 2
2 1
ANS: 4.472

1
0 0
4 0
4
1 1
2 2
3 1
2 -5
ANS: 5.657

1
0 0
0 1
4
-5 -5
-5 5
5 -5
5 5
ANS: IMPOSSIBLE

1
0 0
10000 10000
3
-10000 10000
10000 -10000
10000 10000
ANS: 34142.136

1
0 0
5 5
3
2 2
1 3
5 4
ANS: 7.403

1
5 5
0 0
3
2 2
1 3
5 4
ANS: 7.403

1
0 0
5 5
3
2 2
4 4
5 4
*/