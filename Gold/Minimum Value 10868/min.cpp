#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<int> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L >QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return 1000000000;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
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
    public:
    SegmentTree(int n,vector<int> &data):n(n),st(4*n,1000000000){build(0,0,n-1,data);}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    vector<int> data(n);
    for(int i = 0; i < n; ++i){
        cin>>data[i];
    }
    SegmentTree st(n,data);
    for(int i = 0; i < q; ++i){
        int L,R; cin>>L>>R; --L,--R;
        cout<<st.query(L,R)<<"\n";
    }
}