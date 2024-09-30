#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L > QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    bool mx;
    vector<ll> st;
    void build(int p, int L, int R, vector<ll> &data){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]= mx ? max(st[LC(p)],st[RC(p)]) : min(st[LC(p)],st[RC(p)]);
    }
    ll query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return mx ? -8e18 : 8e18;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        ll l = query(LC(p),L,mid,QL,QR);
        ll r = query(RC(p),mid+1,R,QL,QR);
        return mx ? max(l,r) : min(l,r);
    }
    public:
    SegmentTree(int n, bool mx, vector<ll> &data):n(n),mx(mx),st(4*n){build(0,0,n-1,data);}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    vector<ll> data(n);
    for(int i = 0; i < n; ++i){
        cin>>data[i];
    }
    SegmentTree minSt(n,0,data);
    SegmentTree maxSt(n,1,data);
    for(int i = 0; i < q; ++i){
        int L, R; cin>>L>>R; --L,--R;
        cout<<minSt.query(L,R)<<" "<<maxSt.query(L,R)<<"\n";
    }
}