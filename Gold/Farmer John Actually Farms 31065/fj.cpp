#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
struct Plant{
    ll h,a,t;
    Plant(){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        vector<Plant> p(n);
        for(int i = 0; i < n; ++i)
            cin>>p[i].h;
        for(int i = 0; i < n; ++i)
            cin>>p[i].a;
        for(int i = 0; i < n; ++i)
            cin>>p[i].t;
        sort(p.begin(),p.end(),[](const Plant &a, const Plant &b){return a.t<b.t;});
        ll minD=0,maxD=1e10;
        for(int i = n-1; i > 0; --i){
            Plant &a = p[i-1];
            Plant &b = p[i];
            if(a.h<=b.h){
                if(a.a <= b.a){
                    minD=-1;
                    break;
                }else{
                    minD=max(minD,(b.h-a.h)/(a.a-b.a));
                    minD+=!(a.h+a.a*minD > b.h+b.a*minD);
                }
            }else{
                if(a.a<b.a){
                    maxD=min(maxD,(a.h-b.h)/(b.a-a.a));
                    maxD-=a.h+a.a*maxD==b.h+b.a*maxD;
                }
            }
        }
        cout<<(minD<=maxD?minD:-1)<<"\n";
    }
}
/*
1
3
5 8 4
3 1 3
0 1 2
*/