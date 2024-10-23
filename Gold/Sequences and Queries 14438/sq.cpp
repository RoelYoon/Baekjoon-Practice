#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<int> st;
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    int query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return 1e9;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]=u;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(int n, vector<int> &data):n(n),st(4*n){build(0,0,n-1,data);}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int p, int u){
        update(0,0,n-1,p,p,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n;
    vector<int> data(n);
    for(int i = 0; i < n; ++i)
        cin>>data[i];
    SegmentTree st(n,data);
    cin>>q;
    for(int i = 0; i < q; ++i){
        int t,a,b; cin>>t>>a>>b;
        if(t==1){
            --a;
            st.update(a,b);
        }else{
            --a,--b;
            cout<<st.query(a,b)<<"\n";
        }
    }
}