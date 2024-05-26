#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define ll long long
#define MAX 50005
using namespace std;
struct Cow{
    ll x;
    int w;
    bool d;
    ll minD;
    Cow(ll x, int w, bool d):x(x),w(w),d(d){}
    Cow(){}
};
struct Collision{
    ll time;
    ll colCount;
    ll lastX;
    Collision():time(-1){}
    Collision(ll t, ll c):time(t),colCount(c){}
    Collision(ll t, ll c, ll x):time(t),colCount(c),lastX(x){}
};
vector<Cow> cows;
Collision mem[MAX][2];
int n,B1=0, B2;
Collision nxtCollision(int i,int dir,bool d){
    if(i==-1 || i==n){
        return Collision(-1,-1);
    }
    if(mem[i][d].time!=-1){return mem[i][d];}
    Cow &cur = cows[i];
    if(cur.d != d){
        return mem[i][d]=Collision(0,0,cur.x);
    }
    Collision nxt=nxtCollision(i+dir,dir,d);
    if(nxt.time==-1){return nxt;}
    cur.x += dir*nxt.time;
    ll mid = (nxt.lastX + cur.x)/2;
    ll t = max(abs(mid-nxt.lastX),abs(mid-cur.x));
    return mem[i][d]=Collision(nxt.time+t,nxt.colCount+1,cur.x);
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>B2;
    cows=vector<Cow>(n);
    ll finalW = 0;
    for(int i = 0; i < n; i++){
        int tmpD;
        cin>>cows[i].w>>cows[i].x>>tmpD;
        cows[i].d=tmpD==1;
        finalW+=cows[i].w;
    }finalW/=2;
    sort(cows.begin(),cows.end(),[](const Cow&a, const Cow&b){return a.x<b.x;});
    ll weight=0;
    int j = n-1;
    Collision nxt = nxtCollision(0,1,cows[0].d);
    cout<<"Time: "<<nxt.time<<"\nCollisions: "<<nxt.colCount<<"\n";
}