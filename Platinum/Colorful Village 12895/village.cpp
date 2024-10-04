#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<int> st;
    vector<bool> lazy;
    vector<int> upd;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L > QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]=(1<<upd[p]);
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]=upd[RC(p)]=upd[p];
            }
            lazy[p]=0;
            upd[p]=0;
        }
    }
    int query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR) | query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
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
        st[p]=st[LC(p)] | st[RC(p)];
    }
    public:
    SegmentTree(int n):n(n),st(4*n,2),lazy(4*n),upd(4*n){}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, int z){
        update(0,0,n-1,L,R,z);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,t,q; cin>>n>>t>>q;
    SegmentTree st(n);
    for(int i = 0; i < q; ++i){
        char c; cin>>c;
        int L, R; cin>>L>>R; --L,--R;
        if(L>R){int t = L; L = R; R = t;}
        if(c=='C'){
            int u; cin>>u;
            st.update(L,R,u);
        }else{
            int qr = st.query(L,R), cnt = 0;
            for(int i = 1; i <= t; ++i){
                if(qr & (1<<i)){
                    ++cnt;
                }
            }
            cout<<cnt<<"\n";
        }
    }
}