#include <iostream>
#include <vector>
using namespace std;
struct Pair{
    int id;
    int val;
    Pair(){};
    Pair(int i, int v):id(i),val(v){}
    bool operator<(const Pair &a) const {
        if(val==a.val){
            return id<a.id;
        }
        return val < a.val;
    }
    bool operator==(const Pair &a) const {
        return val == a.val;
    }
};
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<Pair> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L >QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    Pair query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return Pair(-1,1000000005);
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            st[p]=Pair(L,u);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=Pair(L,data[L]);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(int n,vector<int> &data):n(n),st(4*n,Pair(-1,1000000005)){build(0,0,n-1,data);}
    Pair query(int L, int R){
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
    for(int i = 0; i < n; ++i){
        cin>>data[i];
    }
    cin>>q;
    SegmentTree st(n,data);
    for(int i = 0; i < q; ++i){
        int t; cin>>t;
        if(t==1){
            //update
            int p, u; cin>>p>>u; --p;
            st.update(p,u);
        }else{
            int L,R; cin>>L>>R; --L,--R;
            cout<<st.query(L,R).id+1<<"\n";
        }
    }
}