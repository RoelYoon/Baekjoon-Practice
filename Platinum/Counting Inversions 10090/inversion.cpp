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
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        int left = query(LC(p),L,mid,QL,QR);
        int right = query(RC(p),mid+1,R,QL,QR);
        return left+right;
    }
    void update(int p, int L, int R, int QL, int QR, int uVal){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            st[p]=uVal;
            return;
        }
        int mid =(L+R)/2;
        update(LC(p),L,mid,QL,QR,uVal);
        update(RC(p),mid+1,R,QL,QR,uVal);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n):n(n),data(n),st(4*n){}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, int uVal){
        update(0,0,n-1,L,R,uVal);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<int> nums(n);
    SegmentTree st(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i]; nums[i]--;
    }
    long long count = 0;
    for(int i = 0; i < n; i++){
        count+=st.query(nums[i],n-1);
        st.update(nums[i],nums[i],1);
    }
    cout<<count<<"\n";
}