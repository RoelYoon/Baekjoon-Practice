#include <iostream>
#include <vector>
#include <complex>
#include <set>
#include <algorithm>
#define ll long long
#define pt complex<ll>
#define X real()
#define Y imag()
using namespace std;
/*
convex hull layer by layer:

- make convex hull
- remove points in convex hull
- repeat until <=2 points left || prison is included in convex hull
- count how many convex hulls are made
*/
ll cross(pt &a, pt &b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,a,b; cin>>n>>a>>b;
    pt prison(a,b);
    auto cmp = [](const pt &a, const pt &b){
        if(a.X==b.X) return a.Y<b.Y;
        return a.X<b.X;
    };
    set<pt,decltype(cmp)> pts(cmp);
    for(int i = 0; i < n; ++i){
        cin>>a>>b;
        pts.insert(pt(a,b));
    }
    pts.insert(prison);
    int ans = 0;
    bool outside=0;
    while(pts.size() > 2 && !outside){
        set<pt>::iterator it = pts.begin();
        vector<pt> ch{*it,*(++it)};
        // upper hull construction
        int us;
        for(;it!=pts.end(); ++it){
            pt v = ch.back() - ch[ch.size()-2];
            pt v2 = *it - ch.back();
            // ccw = pop
            while(ch.size()>1 && cross(v,v2)>=0){
                ch.pop_back();
                v = ch.back() - ch[ch.size()-2];
                v2 = *it - ch.back();
            }
            ch.push_back(*it);
        }
        us = ch.size()-1;
        // lower hull construction
        set<pt>::reverse_iterator rit = pts.rbegin();
        ch.push_back(*(++rit));
        ++rit;
        for(; rit!=pts.rend(); ++rit){
            pt v = ch.back() - ch[ch.size()-2];
            pt v2 = *rit - ch.back();
            // ccw = pop
            while(ch.size() - us > 1 && cross(v,v2)>=0){
                ch.pop_back();
                v = ch.back() - ch[ch.size()-2];
                v2 = *rit - ch.back();
            }
            ch.push_back(*rit);
        } ch.pop_back();
        // erase points in convex hull
        for(int i = 0; i < ch.size(); ++i){
            if(ch[i]==prison){
                outside=1;
                break;
            }
            pts.erase(ch[i]);
        }
        if(outside) break;
        /*
        cout<<"Convex hull "<<ans+1<<": "<<ch.size()<<"\n";
        for(int i = 0; i < ch.size(); ++i){
            cout<<ch[i]<<" ";
        }cout<<"\n";*/
        ++ans;
    }
    cout<<ans<<"\n";
}   