#include <iostream>
#include <vector>
#define MAX 100005
using namespace std;
class SegmentTree{
    #define LC(p) (2*(p)+1)
    #define RC(p) (2*(p)+2)
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<int> st;
    vector<bool> lazy;
    vector<int> upd;
    void propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]+=upd[p]*(R-L+1);
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]+=upd[p];
                upd[RC(p)]+=upd[p];
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
        return query(LC(p),L,mid,QL,QR) + query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]+=u;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]+=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n):n(n),st(4*n),lazy(4*n),upd(4*n){}
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
    int n; cin>>n;
    SegmentTree st(MAX);
    for(int i = 0; i < n; ++i){
        int L,R; cin>>L>>R; --L, --R;
        int lq = st.query(L,L);
        int rq = st.query(R,R);
        cout<<lq+rq<<"\n";
        if(lq > 0){
            st.update(L,L,-(st.query(L,L)));
        }
        if(rq > 0)
            st.update(R,R,-(st.query(R,R)));
        st.update(L+1,R-1,1);
    }
}
/*
4
1 4
3 7
1 6
2 6
*/