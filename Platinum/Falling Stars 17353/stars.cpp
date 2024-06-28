#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    private:
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    struct Update{
        int UL;
        int UR;
        int s;
        Update(){}
        Update(int L, int R, int s):UL(L),UR(R),s(s){}
    };
    int n;
    vector<ll> &data;
    vector<bool> lazyFlag;
    vector<Update> lazyUpdate;
    ll sum(int s, int n){
        ll total = (n)*(n+1)/2;
        return ((ll)n*(ll)(n+1)/2)-((ll)(s-1)*(s)/2);
    }
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void propagate(int p, int L, int R){
        if(lazyFlag[p]){
            Update &upd = lazyUpdate[p];
            if(L!=R){
                int mid = (L+R)/2;
                if(lazyFlag[LC(p)])
                    propagate(LC(p),L,mid);
                if(lazyFlag[RC(p)])
                    propagate(RC(p),mid+1,R);
                int updMid = (upd.UL+upd.UR)/2;
                Update leftUpdate(upd.UL,mid,upd.s);
                Update rightUpdate(mid+1,upd.UR,upd.s+(upd.UR-upd.UL+1)/2);
                lazyUpdate[LC(p)]=leftUpdate;
                lazyUpdate[RC(p)]=rightUpdate;
                lazyFlag[LC(p)]=lazyFlag[RC(p)]=1;
            }
            lazyFlag[p]=0;
        }
    }
    ll query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return data[L];
        }
        int mid = (L+R)/2;
        ll left = query(LC(p),L,mid,QL,QR);
        ll right = query(RC(p),mid+1,R,QL,QR);
        return left+right;
    }
    void update(int p, int L, int R, int QL, int QR, int s){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            propagate(p,L,R);

            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,s);
        update(RC(p),mid+1,R,QL,QR,s);
    }
    public:
    SegmentTree(vector<ll> &stars):n(stars.size()),data(stars),lazyFlag(4*n),lazyUpdate(4*n){}
    ll query(int x){
        return query(0,0,n-1,x,x);
    }
    void update(int L, int R){
        update(0,0,n-1,L,R,1);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n;
    vector<ll> stars(n);
    for(int i =0; i < n; ++i){
        cin>>stars[i];
    }
    cin>>q;
    SegmentTree st(stars);
    for(int i = 0; i<q; ++i){
        int type; cin>>type;
        if(type==1){
            int L, R; cin>>L>>R;
            st.update(--L,--R);
        }else{
            int x; cin>>x;
            cout<<st.query(--x)<<"\n";
        }
    }
}