#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#define ll long long
#define ld long double
#define pt complex<ll>
#define X real()
#define Y imag()
#define EPS 1e-9
using namespace std;
ll sq(pt p){
    return p.X*p.X+p.Y*p.Y;
}
ld abs(pt p){
    return sqrt(sq(p));
}
struct Circle{
    ll r;
    pt c;
    Circle(){}
    Circle(ll r, pt c):r(r),c(c){}
};
class UnionFind{
    int n;
    vector<int> rep;
    vector<int> rank;
    public:
    UnionFind(int n):n(n),rep(n),rank(n){
        for(int i = 0; i < n; ++i)
            rep[i]=i;
    }
    int find(int p){
        if(rep[p]==p) return p;
        return rep[p]=find(rep[p]);
    }
    void merge(int a, int b){
        a=find(a);
        b=find(b);
        if(rank[a]>rank[b]){
            rep[b]=a;
        }else if(rank[b]>rank[a]){
            rep[a]=b;
        }else{
            rep[b]=a;
            ++rank[a];
        }
    }
    int size(){
        vector<bool> found(n);
        int cnt =0;
        for(int i=0; i < n; ++i){
            cnt+=!found[find(i)];
            found[find(i)]=1;
        }
        return cnt;
    }
};
bool touch(Circle &a, Circle &b){
    ld d = a.r+b.r;
    ld cd = abs(a.c-b.c);
    return cd<d || fabs(cd-d)<EPS;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vector<Circle> circles;
        UnionFind unions(n);
        for(int i = 0; i < n; ++i){
            ll x,y,r; cin>>x>>y>>r;
            circles.push_back({r,{x,y}});
        }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                if(touch(circles[i],circles[j]))
                    unions.merge(i,j);
        cout<<unions.size()<<"\n";
    }
}