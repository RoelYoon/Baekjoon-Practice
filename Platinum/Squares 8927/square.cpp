#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#define ll long long
#define ld long double
#define pt complex<ll>
#define ppt complex<ld>
#define X real()
#define Y imag()
#define nx(p) ((p+1)%m)
#define pv(p) ((p-1+ch.size())%m)
#define EPS 1e-12
using namespace std;
int n;
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(pt p){
    return sqrt((ld)sq(p));
}
ll cross(pt &a, pt b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        cin>>n;
        vector<pt> pts;
        for(int i = 0; i < n; ++i){
            ll x,y,w; cin>>x>>y>>w;
            pts.emplace_back(x,y);
            pts.emplace_back(x+w,y);
            pts.emplace_back(x,y+w);
            pts.emplace_back(x+w,y+w);
        }
        sort(pts.begin(),pts.end(),[](const pt &a, const pt &b){
            if(a.X==b.X) return a.Y<b.Y;
            return a.X<b.X;
        });
        pts.erase(unique(pts.begin(),pts.end()),pts.end());
        n=pts.size();
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
        const int m = ch.size();
        if(m<3){
            if(m==2)
                cout<<sq(ch[0]-ch[1])<<"\n";
            else
                cout<<sq(pts[0]-pts.back())<<"\n";
            return 0;
        }
        ll maxD = 0;
        int j = us;
        bool found[100000]{};
        for(int i = 0; i < m; ++i){
            if(found[i]) continue;
            found[i]=1;
            pt v = ch[nx(i)]-ch[i];
            while(i==j || nx(i)==j ||
            signbit(cross(v,ch[nx(j)]-ch[j]))==signbit(cross(v,ch[j]-ch[pv(j)])))
                j=nx(j);
            maxD=max(maxD,max(sq(ch[i]-ch[j]),sq(ch[nx(i)]-ch[j])));
            if(!cross(v,ch[nx(j)]-ch[j])){
                maxD=max(maxD,max(sq(ch[i]-ch[nx(j)]),sq(ch[nx(i)]-ch[nx(j)])));
                found[j]=1;
            }
        }
        cout<<maxD<<"\n";
    }
}