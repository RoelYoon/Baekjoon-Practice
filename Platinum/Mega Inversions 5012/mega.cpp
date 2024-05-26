#include <iostream>
#include <vector>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    private:
    int n;
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
        int mid=(L+R)/2;
        int left = query(LC(p),L,mid,QL,QR);
        int right = query(RC(p),mid+1,R,QL,QR);
        return left+right;
    }
    void update(int p, int L, int R, int QL, int QR, int d){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            st[p]+=d;
            return;
        }
        int mid=(L+R)/2;
        update(LC(p),L,mid,QL,QR,d);
        update(RC(p),mid+1,R,QL,QR,d);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(vector<int>&data):n(data.size()),st(4*n){}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int p, int d){
        update(0,0,n-1,p,p,d);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i]; nums[i]--;
    }
    SegmentTree leftSt(nums);
    SegmentTree rightSt(nums);
    for(int i = 0; i < n; i++){
        rightSt.update(nums[i],1);
    }
    ll count = 0;
    for(int i = 0; i < n; i++){
        int smallOnRight = rightSt.query(0,nums[i]-1);
        int bigOnLeft = leftSt.query(nums[i]+1,n-1);
        count+=(ll)smallOnRight * (ll)bigOnLeft;
        leftSt.update(nums[i],1);
        rightSt.update(nums[i],-1);
    }
    cout<<count<<"\n";
}