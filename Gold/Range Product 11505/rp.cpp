#include <iostream>
#include <vector>
#define MOD 1000000007
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<ll> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L >QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    ll query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return 1;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return ((query(LC(p),L,mid,QL,QR)%MOD)*(query(RC(p),mid+1,R,QL,QR)%MOD))%MOD;
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            st[p]=u;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=((st[LC(p)]%MOD)*(st[RC(p)]%MOD))%MOD;
    }
    void build(int p, int L, int R, vector<ll> &data){
        if(L==R){
            st[p]=data[L]%MOD;
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=((st[LC(p)]%MOD)*(st[RC(p)]%MOD))%MOD;
    }
    public:
    SegmentTree(int n,vector<ll> &data):n(n),st(4*n){build(0,0,n-1,data);}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int p, int u){
        update(0,0,n-1,p,p,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k,m,q; cin>>n>>k>>m;
    q=k+m;
    vector<ll> data(n);
    for(int i = 0; i < n; ++i){
        cin>>data[i];
    }
    SegmentTree st(n,data);
    for(int i = 0; i < q; ++i){
        int t; cin>>t;
        if(t==1){
            //update
            int p, u; cin>>p>>u; --p;
            st.update(p,u);
        }else{
            int L,R; cin>>L>>R; --L,--R;
            cout<<st.query(L,R)<<"\n";
        }
    }
}