#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<int> st;
    vector<int> upd;
    vector<bool> lazy;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=st[LC(p)]^st[RC(p)];
    }
    void propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]^=upd[p];
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]^=upd[p];
                upd[RC(p)]^=upd[p];
            }
            upd[p]=0;
            lazy[p]=0;
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
        return query(LC(p),L,mid,QL,QR)^query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]^=u;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]^st[RC(p)];
    }
    public:
    SegmentTree(int n, vector<int> &data):n(n),st(4*n),upd(4*n),lazy(4*n){build(0,0,n-1,data);}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, int u){
        update(0,0,n-1,L,R,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n;
    vector<int> data(n);
    for(int i = 0; i < n; ++i)
        cin>>data[i];
    SegmentTree st(n,data);
    cin>>m;
    for(int i = 0; i < m; ++i){
        int type; cin>>type;
        switch(type){
            case 1:
                int L,R,C; cin>>L>>R>>C;
                st.update(L,R,C);
                break;
            case 2:
                int P; cin>>P;
                cout<<st.query(P,P)<<"\n";
                break;
        }
    }
}