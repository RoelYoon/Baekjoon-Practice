#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<ll> st;
    inline bool outBounds(int L, int R, int QL, int QR) {
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR) {
        return L>=QL && R<=QR;
    }
    ll query(int p, int L, int R, int QL, int QR) {
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR)+query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]+=u; 
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p] = st[LC(p)] + st[RC(p)];
    }
    public:
    SegmentTree(int n):n(n),st(4*n){}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int p, int u){
        update(0,0,n-1,p,p,u);
    }
};
struct Pair{
    int L,R;
    Pair(){}
    Pair(int L, int R):L(L),R(R){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    for(int i = 0; i < t; ++i){
        ll cnt = 0;
        int n,m,k; cin>>n>>m>>k;
        vector<Pair> pairs(k);
        SegmentTree st(m);
        for(int i = 0; i < k; ++i) {
            cin>>pairs[i].L>>pairs[i].R;
            --pairs[i].L,--pairs[i].R;
        }
        sort(pairs.begin(),pairs.end(),[](const Pair &a, const Pair &b){
            if(a.L==b.L) return a.R<b.R;
            return a.L<b.L;        
        });
        for(int i = 0; i < k; ++i) {
            cnt += st.query(pairs[i].R+1,m-1);
            st.update(pairs[i].R,1);
        }
        cout<<"Test case "<<i+1<<": "<<cnt<<"\n";
    }
}