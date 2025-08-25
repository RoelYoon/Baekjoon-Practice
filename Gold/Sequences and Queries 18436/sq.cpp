#include <iostream>
#include <vector>
#define ll long long
using namespace std;
struct Element{
    int even=0;
    int odd=0;
    Element(){}
    Element(int e, int o):even(e),odd(o){}
    void leaf_update(ll v){
        odd=v%2;
        even=!(v%2);
    }
};
class SegmentTree{
    #define LC(i) (2*i+1)
    #define RC(i) (2*i+2)
    int n;
    vector<Element> st; 
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void build(int p, int L, int R, vector<ll> &data){
        if(L==R){
            st[p].even=!(data[L]%2);
            st[p].odd=data[L]%2;
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p].even=st[LC(p)].even + st[RC(p)].even;
        st[p].odd=st[LC(p)].odd + st[RC(p)].odd;
    }
    void update(int p, int L, int R, int QL, int QR, ll v){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p].leaf_update(v);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,v);
        update(RC(p),mid+1,R,QL,QR,v);
        st[p].even=st[LC(p)].even + st[RC(p)].even;
        st[p].odd=st[LC(p)].odd + st[RC(p)].odd;
    }
    int query(int p, int L, int R, int QL, int QR, bool evenType){
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return (evenType?st[p].even:st[p].odd);
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR,evenType)+query(RC(p),mid+1,R,QL,QR,evenType);
    }
    public:
    SegmentTree(int n, vector<ll> &data):n(n),st(4*n){build(0,0,n-1,data);}
    int query(int L, int R, bool evenType){
        return query(0,0,n-1,L,R,evenType);
    }
    void update(int P, ll v){
        update(0,0,n-1,P,P,v);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n;
    vector<ll> data(n);
    for(int i = 0; i < n; ++i)
        cin>>data[i];
    SegmentTree st(n,data);
    cin>>q;
    for(int i = 0; i < q; ++i){
        int t; cin>>t;
        if(t==1){
            int P,v; cin>>P>>v; --P;
            st.update(P,v);
        }else{
            int L, R; cin>>L>>R; --L,--R;
            cout<<st.query(L,R,t==2)<<"\n";
        }
    }
}