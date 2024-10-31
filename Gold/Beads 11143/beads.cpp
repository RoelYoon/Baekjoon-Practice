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
    int query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR) + query(RC(p),mid+1,R,QL,QR);
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
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n):n(n),st(4*n){}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int P, int u){
        update(0,0,n-1,P,P,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n,q1,q2,q; cin>>n>>q1>>q2; q=q1+q2;
        SegmentTree st(n);
        for(int i = 0; i < q; ++i){
            char qt; cin>>qt;
            if(qt=='P'){
                //update
                int i,a; cin>>i>>a; --i;
                st.update(i,a);
            }else{
                int a,b; cin>>a>>b; --a,--b;
                cout<<st.query(a,b)<<"\n";
            }
        }
    }
}