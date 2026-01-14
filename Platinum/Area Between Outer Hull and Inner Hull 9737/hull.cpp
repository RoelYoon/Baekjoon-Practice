#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <algorithm>
#include <set>
#define ld long double
#define ll long long
#define pt complex<ld>
#define X real()
#define Y imag()
using namespace std;
inline ld cross(pt &a, pt &b){
    return (conj(a)*b).Y;
}
ld area(vector<pt> &pts){
    if(pts.size() < 3)
        return 0;
    ld a = 0;
    for(int i = 0; i < pts.size()-1; ++i){
        a+=cross(pts[i],pts[i+1]);
    }
    a+=cross(pts.back(), pts[0]);
    return abs(a)/2.0L;
}
auto cmp = [](const pt &a, const pt &b){
    if(a.X==b.X){
        return a.Y<b.Y;
    }
    return a.X<b.X;
};
void convex_hull(set<pt,decltype(cmp)> &pts, vector<pt> &ch){
    if(pts.size()<3)
        return;
    set<pt>::iterator it = pts.begin();
    ch.push_back(*it);
    ch.push_back(*(++it));
    ++it;
    for(; it!=pts.end(); ++it){
        pt v = ch.back() - ch[ch.size()-2];
        pt v2 = (*it) - ch.back();
        while(ch.size()>1 && cross(v,v2)>=0){
            ch.pop_back();
            v = ch.back() - ch[ch.size()-2];
            v2 = *it - ch.back();
        }
        ch.push_back(*it);
    }
    int us = ch.size()-1;
    set<pt>::reverse_iterator rit = pts.rbegin();
    ch.push_back(*(++rit));
    for(; rit!=pts.rend(); ++rit){
        pt v = ch.back() - ch[ch.size()-2];
        pt v2 = *rit - ch.back();
        while(ch.size()-us>1 && cross(v,v2)>=0){
            ch.pop_back();
            v = ch.back() - ch[ch.size()-2];
            v2 = *rit - ch.back();
        }
        ch.push_back(*rit);
    } ch.pop_back();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string id; int n;
    while(cin>>id>>n){
        if(id=="ZZ" && n==0)
            return 0;
        set<pt,decltype(cmp)> pts(cmp);
        for(int i = 0; i < n; ++i){
            ld x,y; cin>>x>>y;
            pts.insert(pt(x,y));
        }
        vector<pt> ch1;
        vector<pt> ch2;
        convex_hull(pts,ch1);
        for(int i = 0; i < ch1.size(); ++i){
            pts.erase(ch1[i]);
        }
        convex_hull(pts,ch2);
        cout<<"ProblemID "<<id<<": ";
        cout<<fixed<<setprecision(4)<<area(ch1)-area(ch2)<<"\n";
    }
}