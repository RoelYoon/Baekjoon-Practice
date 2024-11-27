#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#define ll long long
#define pt complex<ll>
#define X real()
#define Y imag()
#define nx(p) ((p+1)%m)
#define pv(p) ((p-1+m)%m)
using namespace std;
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vector<pt> pts;
        for(int i = 0; i < n; ++i){
            int x,y; cin>>x>>y;
            pts.emplace_back(x,y);
        }
        sort(pts.begin(),pts.end(),[](const pt&a, const pt&b){
            if(a.X==b.X) return a.Y<b.Y;
            return a.X<b.X;
        });
        vector<pt> ch{pts[0],pts[1]};
        int us=0;
        for(int i=2; us?i>=0:i<n; us?--i:++i){
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
            if(i==n-1){
                us=ch.size()-1;
                ch.push_back(pts[--i]);
            }
        }ch.pop_back();
        const int m = ch.size();
        if(m<3){
            if(m==2)
                cout<<ch[0].X<<" "<<ch[0].Y<<" "<<ch.back().X<<" "<<ch.back().Y<<"\n";
            else
                cout<<pts[0].X<<" "<<pts[0].Y<<" "<<pts.back().X<<" "<<pts.back().Y<<"\n";
            continue;
        }
        int j = 0;
        ll maxD=-1;
        pt p1,p2;
        vector<bool> found(m);
        for(int i = 0; i < m; ++i){
            if(found[i]) continue;
            found[i]=1;
            pt v = ch[nx(i)]-ch[i];
            while(i==j || nx(i)==j ||
            signbit(cross(v,ch[nx(j)]-ch[j]))==signbit(cross(v,ch[j]-ch[pv(j)])))
                j=nx(j);
            if(sq(ch[i]-ch[j])>maxD){
                maxD=sq(ch[i]-ch[j]);
                p1=ch[i];
                p2=ch[j];
            }
            if(sq(ch[nx(i)]-ch[j])>maxD){
                maxD=sq(ch[nx(i)]-ch[j]);
                p1=ch[nx(i)];
                p2=ch[j];
            }
            if(!cross(v,ch[nx(j)]-ch[j])){
                if(sq(ch[i]-ch[nx(j)])>maxD){
                    maxD=sq(ch[i]-ch[nx(j)]);
                    p1=ch[i];
                    p2=ch[nx(j)];
                }
                if(sq(ch[nx(i)]-ch[nx(j)])>maxD){
                    maxD=sq(ch[nx(i)]-ch[nx(j)]);
                    p1=ch[nx(i)];
                    p2=ch[nx(j)];
                }
                found[j]=1;
            }
        }
        cout<<p1.X<<" "<<p1.Y<<" "<<p2.X<<" "<<p2.Y<<"\n";
    }
}