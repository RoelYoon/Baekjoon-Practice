#include <iostream>
#include <vector>
#define ll long long
#define MAX 100005
using namespace std;
ll diffArr[MAX];
ll gcd(ll a, ll b){
    return b==0 ? a : gcd(b,a%b);
}
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    int n;
    vector<ll> st;
    vector<ll> rep;
    vector<ll> diffGCD;
    vector<bool> lazy;
    vector<ll> upd;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L > QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void propagate(int p, int L, int R){
        if(lazy[p]){
            if(L!=R){
                rep[p]+=upd[p];
                st[p]=gcd(rep[p],diffGCD[p]);
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]+=upd[p];
                upd[RC(p)]+=upd[p];
            }else{
                st[p]+=upd[p];
            }
            lazy[p]=0;
            upd[p]=0;
        }
    }
    ll query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        ll left = query(LC(p),L,mid,QL,QR);
        ll right = query(RC(p),mid+1,R,QL,QR);
        return gcd(left,right);
    }
    void update(int p, int L, int R, int QL, int QR, ll u){
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
        st[p]=gcd(st[LC(p)],st[RC(p)]);
    }
    void build(int p, int L, int R, int data[MAX]){
        if(L==R){
            st[p]=data[L];
            rep[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=gcd(st[LC(p)],st[RC(p)]);
        rep[p]=rep[LC(p)]!=0 ? rep[LC(p)] : rep[RC(p)];
        ll GCD=0;
        for(int i = L; i <= R; ++i)
            GCD=gcd(GCD,diffArr[i]);
        diffGCD[p]=GCD;
    }
    public:
    SegmentTree(int n,int data[MAX]):n(n),st(4*n),lazy(4*n),rep(4*n),upd(4*n),diffGCD(4*n){build(0,0,n-1,data);}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, ll u){
        update(0,0,n-1,L,R,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q, data[MAX]; cin>>n;
    for(int i = 0; i < n; ++i)
        cin>>data[i];
    diffArr[0]=data[0];
    for(int i = 1; i < n; ++i)
        diffArr[i]=abs(data[i]-data[i-1]);
    SegmentTree st(n,data);
    cin>>q;
    for(int i = 0; i < q; ++i){
        ll t; int L, R; cin>>t>>L>>R; --L; --R;
        if(t==0){
            cout<<st.query(L,R)<<"\n";
        }else{
            st.update(L,R,t);
        }
    }
}