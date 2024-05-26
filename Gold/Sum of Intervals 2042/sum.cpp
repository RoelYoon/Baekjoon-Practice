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
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    ll query(int p, int L, int R, int QL, int QR){
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
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            st[p]=d;
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
    SegmentTree(vector<ll>&a):n(a.size()),data(a),st(4*n){build(0,0,n-1);}
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
        ll a,b,c;
        cin>>a>>b>>c;
        if(a==1){
            // update
            b--;
            st.update(b,b,c);
        }else{
            // query
            b--;c--;
            cout<<st.query(b,c)<<"\n";
        }
    }
}