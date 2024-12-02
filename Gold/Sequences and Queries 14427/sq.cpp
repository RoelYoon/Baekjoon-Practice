#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    struct Node{
        int i,v;
        Node(){}
        Node(int i, int v):i(i),v(v){}
        bool operator<(const Node&k) const {
            if(v==k.v) return i<k.i;
            return v<k.v;
        }
    };
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<Node> st;
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=Node(L,data[L]);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    Node query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return Node(1e9,1e9);
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]=Node(L,u);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(int n,vector<int>&data):n(n),st(4*n){build(0,0,n-1,data);}
    void update(int p, int v){
        update(0,0,n-1,p,p,v);
    }
    Node query(int L, int R){
        return query(0,0,n-1,L,R);
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
        int t; cin>>t;
        if(t==1){
            int p,v;
            cin>>p>>v; --p;
            st.update(p,v);
        }else{
            cout<<st.query(0,n-1).i+1<<"\n";
        }
    }
}