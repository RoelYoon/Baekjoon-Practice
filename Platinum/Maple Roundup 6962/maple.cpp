#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>
using namespace std;
#define ll long long
#define ld long double
#define pt complex<ll>
#define X real()
#define Y imag()
ll sq(pt p){
    return p.X*p.X + p.Y*p.Y;
}
ll cross(pt &a, pt &b){
    return (conj(a)*b).Y;
}
int main(){
    int t; scanf("%d",&t);
    while(t--){
        int n; scanf("%d", &n);
        vector<pt> pts(n);
        for(int i = 0; i < n; ++i){
            int x,y; 
            scanf("%d %d", &x, &y);
            pts[i]=pt(x,y);
        }
        sort(pts.begin(),pts.end(),[](const pt &a, const pt &b){
            if(a.X==b.X) return a.Y<b.Y;
            return a.X<b.X;
        });
        ld length = 0;
        if(n==2){
            printf("%.2Lf\n",(sqrtl(sq(pts[1]-pts[0])))*2.0L);
            continue;
        }
        vector<pt> ch{pts[0], pts[1]};
        for(int i = 0; i < n; ++i){
            pt v = ch.back()-ch[ch.size()-2];
            pt v2 = pts[i]-ch.back();
            while(ch.size() > 1 && cross(v,v2)>=0){
                ch.pop_back();
                v = ch.back()-ch[ch.size()-2];
                v2 = pts[i]-ch.back();
            }
            ch.push_back(pts[i]);
        }
        int us = ch.size()-1;
        ch.push_back(pts[n-2]);
        for(int i = n-3; i >= 0; --i){
            pt v = ch.back()-ch[ch.size()-2];
            pt v2 = pts[i]-ch.back();
            while(ch.size()-us > 1 && cross(v,v2)>=0){
                ch.pop_back();
                v = ch.back()-ch[ch.size()-2];
                v2 = pts[i]-ch.back();
            }
            ch.push_back(pts[i]);
        }
        ch.pop_back();
        for(int i = 0; i < ch.size(); ++i){
            length+=sqrtl(sq(ch[i]-ch[(i+1)%ch.size()]));
        }
        printf("%.2Lf\n",length);
    }
}