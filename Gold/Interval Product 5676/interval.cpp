#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<ll> st;
    void build(int p, int L, int R, vector<ll> &data){
        if(L==R){
            // leaf node
            st[p]=(data[L]==0?0:(data[L]<0?-1:1));
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p] = st[LC(p)] * st[RC(p)];
    }
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    ll query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return 1;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR)*query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, ll u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p] = (u==0?0:(u<0?-1:1));
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]*st[RC(p)];
    }
    public:
    SegmentTree(int n,vector<ll> &data):n(n),st(4*n){build(0,0,n-1,data);}
    int query(int L, int R){
        if(R<L){
            int t = L;
            L = R;
            R = t;
        }
        return query(0,0,n-1,L,R);
    }
    void update(int P, ll u){
        update(0,0,n-1,P,P,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q;
    while(cin>>n>>q){
        vector<ll> data(n);
        for(int i = 0; i < n; ++i){
            cin>>data[i];
        }
        SegmentTree st(n,data);
        string ans = "";
        for(int i = 0; i < q; ++i){
            char t; cin>>t;
            if(t=='C'){
                // update
                int p; ll u; cin>>p>>u;
                --p;
                st.update(p,u);
            }else{
                // query
                int l,r; cin>>l>>r;
                --l,--r;
                int qAns = st.query(l,r);
                ans+=(qAns==0?'0':(qAns<0?'-':'+'));
            }
        }
        cout<<ans<<"\n";
    }
}