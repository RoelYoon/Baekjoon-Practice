#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    inline bool outBounds(int L, int R, int QL, int QR){return R<QL || L>QR;}
    inline bool inBounds(int L, int R, int QL, int QR){return L>=QL && R<=QR;}
    int n;
    bool minType;
    vector<ll> st;
    vector<ll> upd;
    vector<bool> lazy;
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=minType?min(st[LC(p)],st[RC(p)]):st[LC(p)]+st[RC(p)];
    }
    void propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]+=minType?upd[p]:(ll)(R-L+1)*upd[p];
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]+=upd[p];
                upd[RC(p)]+=upd[p];
            }
            upd[p]=0;
            lazy[p]=0;
        }
    }
    ll query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return minType?9e18:0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        ll left = query(LC(p),L,mid,QL,QR);
        ll right = query(RC(p),mid+1,R,QL,QR);
        return minType?min(left,right):left+right;
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]+=u;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=minType?min(st[LC(p)],st[RC(p)]):st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n, bool isMin, vector<int> &data):n(n), minType(isMin), st(4*n), lazy(4*n), upd(4*n){build(0,0,n-1,data);}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, int u){
        update(0,0,n-1,L,R,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    vector<int> data(n);
    for(int i = 0; i < n; ++i)
        cin>>data[i];
    SegmentTree mSt(n,1,data),sSt(n,0,data);
    for(int i = 0; i < q; ++i){
        char type;
        int L, R;
        cin>>type>>L>>R; --L,--R;
        switch(type){
            case 'M':
                cout<<mSt.query(L,R)<<"\n";
                break;
            case 'P':
                int u; cin>>u;
                mSt.update(L,R,u);
                sSt.update(L,R,u);
                break;
            case 'S':
                cout<<sSt.query(L,R)<<"\n";
                break;
        }
    }
}