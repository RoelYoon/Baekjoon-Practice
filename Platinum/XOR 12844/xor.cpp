#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    private:
    int n;
    vector<int> data;
    vector<int> st;
    vector<bool> lazyFlag;
    vector<int> lazyUpdate;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
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
        st[p]=st[LC(p)]^st[RC(p)];
    }
    void propagate(int p, int L, int R){
        if(lazyFlag[p]){
            st[p]^=(R-L+1)%2==0?0:lazyUpdate[p];
            if(L!=R){
                lazyFlag[LC(p)]=lazyFlag[RC(p)]=1;
                int mid = (L+R)/2;
                lazyUpdate[LC(p)]^=lazyUpdate[p];
                lazyUpdate[RC(p)]^=lazyUpdate[p];
            }
            lazyFlag[p]=0;
            lazyUpdate[p]=0;
        }
    }
    int query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        int left  = query(LC(p),L,mid,QL,QR);
        int right = query(RC(p),mid+1,R,QL,QR);
        return left ^ right; 
    }
    void update(int p, int L, int R, int QL, int QR, int d){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazyFlag[p]=1;
            lazyUpdate[p]^=d;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,d);
        update(RC(p),mid+1,R,QL,QR,d);
        st[p]=st[LC(p)]^st[RC(p)];
    }
    public:
    SegmentTree(vector<int> &data):n(data.size()),data(data),st(4*n),lazyFlag(4*n),lazyUpdate(4*n){build(0,0,n-1);}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, int d){
        update(0,0,n-1,L,R,d);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    SegmentTree st(nums);
    int m; cin>>m;
    for(int i = 0; i < m; i++){
        int t; cin>>t;
        if(t==1){
            int a,b,k; cin>>a>>b>>k;
            st.update(a,b,k);
        }else{
            int a,b; cin>>a>>b;
            cout<<st.query(a,b)<<"\n";
        }
    }
}