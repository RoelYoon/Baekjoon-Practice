#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L > QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    bool mx;
    vector<int> st;
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]= mx ? max(st[LC(p)],st[RC(p)]) : min(st[LC(p)],st[RC(p)]);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            st[p]=u;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p] = mx ? max(st[LC(p)],st[RC(p)]) : min(st[LC(p)],st[RC(p)]);
    }
    int query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return mx ? 0 : 1000000000;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        int l = query(LC(p),L,mid,QL,QR);
        int r = query(RC(p),mid+1,R,QL,QR);
        return mx ? max(l,r) : min(l,r);
    }
    public:
    SegmentTree(int n, bool mx, vector<int> &data):n(n),mx(mx),st(4*n){build(0,0,n-1,data);}
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
    int t; cin>>t;
    while(t--){
        int n,k; cin>>n>>k;
        vector<int> data(n);
        for(int i = 0; i < n; ++i){
            data[i]=i;
        }
        SegmentTree maxSt(n,1,data);
        SegmentTree minSt(n,0,data);
        for(int i = 0; i < k; ++i){
            bool q; cin>>q;
            if(q){
                int L, R; cin>>L>>R;
                cout<<((minSt.query(L,R)==L && maxSt.query(L,R)==R) ? "YES" : "NO")<<"\n";
            }else{
                int a, b; cin>>a>>b;
                maxSt.update(a,data[b]);
                maxSt.update(b,data[a]);
                minSt.update(a,data[b]);
                minSt.update(b,data[a]);
                int t = data[a];
                data[a] = data[b];
                data[b] = t;
            }
        }
    }
}