#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    private:
    int n;
    vector<vector<int>> st;
    vector<int> &data;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void build(int p, int L, int R){
        if(L==R){
            st[p]=vector<int>(1,data[L]);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid);
        build(RC(p),mid+1,R);
        vector<int> &left = st[LC(p)];
        vector<int> &right = st[RC(p)];
        st[p]=vector<int>(left.size()+right.size());
        vector<int> &cur = st[p];
        int LP = 0, RP = 0, CP=0;
        while(LP < left.size() && RP < right.size()){
            if(left[LP] < right[RP]){
                cur[CP++]=left[LP++];
            }else{
                cur[CP++]=right[RP++];
            }
        }
        while(LP < left.size())
            cur[CP++]=left[LP++];
        while(RP < right.size())
            cur[CP++]=right[RP++];
    }
    int query(int p, int L, int R, int QL, int QR, int k){
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return (R-L+1)-(upper_bound(st[p].begin(),st[p].end(),k)-st[p].begin());
        }
        int mid = (L+R)/2;
        int left = query(LC(p),L,mid,QL,QR,k);
        int right = query(RC(p),mid+1,R,QL,QR,k);
        return left + right;
    }
    public:
    SegmentTree(vector<int> &data):n(data.size()),data(data),st(4*n){build(0,0,n-1);}
    int query(int L, int R, int k){
        return query(0,0,n-1,L,R,k);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++)
        cin>>nums[i];
    SegmentTree st(nums);
    int q,lastAns=0; cin>>q;
    while(q--){
        int i,j,k; cin>>i>>j>>k; 
        i^=lastAns;
        j^=lastAns;
        k^=lastAns;
        i--; j--;
        lastAns = st.query(i,j,k);
        cout<<lastAns<<"\n";
    }
}