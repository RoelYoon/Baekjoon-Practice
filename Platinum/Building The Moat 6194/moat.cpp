#include <cstdio>
#include <complex>
#include <vector>
#include <algorithm>
#include <cmath>
#define ll long long
#define ld long double
#define pt complex<ll>
#define X real()
#define Y imag()
using namespace std;
ll cross(pt &a, pt &b){
    return (conj(a)*b).Y;
}
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
int main(){
    int n; scanf("%d",&n);
    vector<pt> pts(n);
    for(int i = 0; i < n; ++i){
        int x,y; scanf("%d %d", &x, &y);
        pts[i]=pt(x,y);
    }
    ld length = 0;
    sort(pts.begin(), pts.end(), [](const pt&a, const pt&b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    });
    if(n<2){
        printf("0.00\n");
        return 0;
    }
    if(n==2){
        printf("%.2Lf", sqrtl(sq(pts[0]-pts[1])));
        return 0;
    }
    if(n==3){
        for(int i = 0; i < n; ++i){
            length+=sqrtl(sq(pts[i]-pts[(i+1)%n]));
        }
        printf("%.2Lf", length);
        return 0;
    }
    vector<pt> ch{pts[0],pts[1]};
    for(int i = 2; i < n; ++i){
        pt v = ch.back() - ch[ch.size()-2];
        pt v2 = pts[i] - ch.back();
        while(ch.size()>1 && cross(v,v2)>=0){
            ch.pop_back();
            v = ch.back() - ch[ch.size()-2];
            v2 = pts[i] - ch.back();
        }
        ch.push_back(pts[i]);
    }
    int us = ch.size()-1;
    ch.push_back(pts[n-2]);
    for(int i = n-3; i >= 0; --i){
        pt v = ch.back() - ch[ch.size()-2];
        pt v2 = pts[i] - ch.back();
        while(ch.size()-us>1 && cross(v,v2)>=0){
            ch.pop_back();
            v = ch.back() - ch[ch.size()-2];
            v2 = pts[i] - ch.back();
        }
        ch.push_back(pts[i]);
    } ch.pop_back();
    for(int i = 0; i < ch.size()-1; ++i){
        length+=sqrtl(sq(ch[i]-ch[i+1]));
    }
    length+=sqrtl(sq(ch[ch.size()-1]-ch[0]));
    printf("%.2Lf", length);
}