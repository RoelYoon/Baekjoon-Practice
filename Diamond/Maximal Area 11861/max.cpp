#include <iostream>
#include <vector>
#define ll long long
using namespace std;
// maximal histogram area problem w/ divide and conquer + segment tree
struct Node{
    int ind;
    ll value;
    Node(){};
    Node(int i, ll v):ind(i),value(v){};
    bool operator<(const Node &s) const {
        return value<s.value;
    }
};
struct SegmentTree{
    #define INF 1e15
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    private:
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<Node> st;
    void build(int p, int L, int R, vector<Node> &data){
        if(L==R){
            // leaf node
            st[p] = data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    Node query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return Node(-1,INF);
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    public:
    Node query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    // static ; no update
    SegmentTree(int n,vector<Node> &data):n(n),st(4*n){
        build(0,0,n-1,data);
    }
};
ll maxArea(int L, int R, SegmentTree &st){
    if(L==R){
        // base case
        return st.query(L,R).value*(R-L+1);
    }
    // second base case
    if(R<L){
        return 0;
    }
    Node cur = st.query(L,R); // mid is cur.ind
    // case work
    return max(cur.value*(R-L+1),max(maxArea(L,cur.ind-1,st),maxArea(cur.ind+1,R,st)));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Node> data(n);
    for(int i = 0; i < n; ++i){
        cin>>data[i].value;
        data[i].ind = i;
    }
    SegmentTree st(n,data);
    // divide and conquer
    cout<<maxArea(0,n-1,st)<<"\n";
}