#include <iostream>
#include <vector>
#define MAX 100005
#define ll long long
using namespace std;
ll a[MAX];
struct Pair{
    ll val;
    int i;
    Pair(){}
    Pair(ll v, int i):val(v),i(i){}
    bool operator<(const Pair &other) const {
        return val < other.val;
    }
    bool operator>(const Pair &other) const {
        return val > other.val;
    }
};
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L > QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<Pair> st;
    vector<bool> lazy;
    vector<ll> upd;
    bool mx;
    void build(int p, int L, int R, ll data[MAX]){
        if(L==R){
            st[p]=Pair(data[L],L);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=mx?max(st[LC(p)],st[RC(p)]):min(st[LC(p)],st[RC(p)]);
    }
    void propagate(int p, int L, int R){
        if(lazy[p]){
            st[p].val=upd[p]*(ll)(R-L+1);
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]=upd[p];
                upd[RC(p)]=upd[p];
            }
            upd[p]=0;
            lazy[p]=0;
        }
    }
    Pair query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return mx?Pair(0,-1):Pair(1000000000,-1);
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return mx?max(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR)) : min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    void update(int p, int L, int R, int QL, int QR, ll u){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]=u;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=mx?max(st[LC(p)],st[RC(p)]):min(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(int n,ll data[MAX],bool mx):n(n),st(4*n),lazy(4*n),upd(4*n),mx(mx){build(0,0,n-1,data);}
    Pair query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int P, ll u){
        update(0,0,n-1,P,P,u);
    }
};  
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i = 0 ;i < n; ++i){
        cin>>a[i];
    }
    SegmentTree maxSt(n,a,1);
    int q; cin>>q;
    for(int i = 0; i < q; ++i){
        int t; cin>>t;
        if(t==1){
            int p,v; cin>>p>>v; --p;
            maxSt.update(p,v);
        }else{
            int l,r; cin>>l>>r; --l,--r;
            Pair mxQ = maxSt.query(l,r);
            maxSt.update(mxQ.i,0);
            cout<<mxQ.val+maxSt.query(l,r).val<<"\n";
            maxSt.update(mxQ.i,mxQ.val);
        }
    }
}