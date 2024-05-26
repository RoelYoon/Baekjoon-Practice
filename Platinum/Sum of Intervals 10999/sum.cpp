#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    private:
    int n;
    vector<ll> data;
    vector<ll> st;
    vector<bool> lazyFlag;
    vector<ll> lazyUpdate;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void propagate(int p, int L, int R){
        if(lazyFlag[p]){
            st[p]+=(R-L+1)*lazyUpdate[p];
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
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        ll left = query(LC(p),L,mid,QL,QR);
        ll right = query(RC(p),mid+1,R,QL,QR);
        return left + right;
    }
    void update(int p, int L, int R, int QL, int QR, ll d){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazyFlag[p]=1;
            lazyUpdate[p]+=d;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,d);
        update(RC(p),mid+1,R,QL,QR,d);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    void build(int p, int L, int R){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid);
        build(RC(p),mid+1,R);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(vector<ll>&a):n(a.size()),data(a),st(4*n),lazyFlag(4*n),lazyUpdate(4*n){build(0,0,n-1);}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, ll d){
        update(0,0,n-1,L,R,d);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,k; cin>>n>>m>>k;
    vector<ll> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    SegmentTree st(nums);
    for(int i = 0; i < (m+k); i++){
        int q, L, R;
        cin>>q>>L>>R; L--; R--;
        if(q==1){
            // update
            ll d; cin>>d;
            st.update(L,R,d);
        }else{
            // query
            cout<<st.query(L,R)<<"\n";
        }
    }
}
/*
5 7 4
983258932 983258932 983258932 983258932 983258932
2 1 5
1 1 5 99999999
2 1 5
1 1 4 99999999
2 1 5
1 1 4 99999999
2 1 5
1 3 5 99999999
2 5 5
1 1 5 -99999999
2 1 5

10 5 2
128947128
523982355
589435345
235091585
928353241
124789151
643683469
198623896
983258932
235892355
2 1 10
1 1 5 99999999
2 1 10
1 1 4 99999999
2 1 10
1 1 9 99999999
2 1 5


*/