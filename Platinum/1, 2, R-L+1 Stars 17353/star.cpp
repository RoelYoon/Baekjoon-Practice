#include <iostream>
#include <vector>
#define MAX 100005
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    int n;
    vector<ll> st;
    vector<ll> lazyUpdate;
    vector<bool> lazyFlag;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void propagate(int p, int L, int R){
        if(lazyFlag[p]){
            st[p] += (R-L+1) * lazyUpdate[p];
            if(L!=R){
                lazyFlag[LC(p)]=lazyFlag[RC(p)]=1;
                lazyUpdate[LC(p)]+=lazyUpdate[p];
                lazyUpdate[RC(p)]+=lazyUpdate[p];
            }
            lazyFlag[p]=0;
            lazyUpdate[p]=0;
        }
    }
    ll query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        ll left = query(LC(p),L,mid,QL,QR);
        ll right = query(RC(p),mid+1,R,QL,QR);
        return left + right;
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        propagate(p, L, R);
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            lazyFlag[p]=1;
            lazyUpdate[p]+=u;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n, int data[MAX]):n(n),st(4*n),lazyUpdate(4*n),lazyFlag(4*n){
        build(data,0,0,n-1);
    }
    void build(int data[MAX], int p, int L, int R){
        if(L==R){
            st[p] = data[L];
            return;
        }
        int mid = (L+R)/2;
        build(data,LC(p),L,mid);
        build(data,RC(p),mid+1,R);
        st[p]=st[LC(p)]+st[RC(p)];
    }
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
    int n; cin>>n;
    int stars[MAX]{};
    int diff[MAX]{};
    for(int i = 0; i < n; ++i)
        cin>>stars[i];
    diff[0]=stars[0];
    for(int i = 1; i < n; ++i)
        diff[i] = stars[i]-stars[i-1];
    SegmentTree st(n,diff);
    int q; cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            //update
            int L, R; cin>>L>>R; --L; --R;
            st.update(L,R,1);
            if(R!=n-1)
                st.update(R+1,R+1,-(R-L+1));
        }else{
            //query
            int p; cin>>p; --p;
            cout<<st.query(0,p)<<"\n";
        }
    }
}