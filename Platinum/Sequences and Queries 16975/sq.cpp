#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    private:
    int n;
    vector<ll> st;
    vector<ll> data;
    vector<bool> lazyFlag;
    vector<ll> lazyUpdate;
    bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
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
    void propagate(int p, int L, int R){
        if(lazyFlag[p]){
            st[p]+=lazyUpdate[p]*(R-L+1);
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
        return left+right;
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
    public:
    SegmentTree(vector<ll> &data):n(data.size()),st(4*n),data(data),lazyFlag(4*n),lazyUpdate(4*n){build(0,0,n-1);};
    ll query(int p){
        return query(0,0,n-1,p,p);
    }
    void update(int L, int R, ll d){
        update(0,0,n-1,L,R,d);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<ll> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    SegmentTree st(nums);
    int m; cin>>m;
    for(int i = 0 ; i < m; i++){
        int t; cin>>t;
        if(t==1){
            //update
            ll L, R, d; cin>>L>>R>>d;
            L--; R--;
            st.update(L,R,d);
        }else{
            //query
            int p; cin>>p; p--;
            cout<<st.query(p)<<"\n";
        }
    }
}