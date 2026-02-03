#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<ll> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    ll query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR) + query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, ll u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]+=u;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n):n(n),st(4*n){}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, ll u){
        update(0,0,n-1,L,R,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    SegmentTree st(n);
    for(int i=0; i<q; ++i){
        int t; cin>>t;
        if(t==1){
            ll x; int p; cin>>p>>x;
            --p;
            st.update(p,p,x);
        }else{
            int L,R; cin>>L>>R;
            --L,--R;
            cout<<st.query(L,R)<<"\n";
        }
    }
}