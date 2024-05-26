#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define ll long long
#define MAX 5000000
using namespace std;
class SegmentTree{
    private:
    struct Node{
        Node *LC=nullptr;
        Node *RC=nullptr;
        ll val;
        Node():val(0){}
        Node(ll v):val(v){}
        ~Node(){
            delete LC;
            delete RC;
        }
    };
    ll n;
    Node root;
    inline bool outBounds(ll L, ll R, ll QL, ll QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(ll L, ll R, ll QL, ll QR){
        return L>=QL && R<=QR;
    }
    void update(Node* cur, ll L, ll R, ll QL, ll QR, ll d){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            cur->val = d;
            return;
        }
        ll mid = (L+R)/2;
        if(cur->LC==nullptr){
            cur->LC=new Node(0);
        }
        if(cur->RC==nullptr){
            cur->RC=new Node(0);
        }
        update(cur->LC,L,mid,QL,QR,d);
        update(cur->RC,mid+1,R,QL,QR,d);
        cur->val = cur->LC->val + cur->RC->val;
    }
    ll query(Node* cur, ll L, ll R, ll QL, ll QR){
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return cur->val;
        }
        ll left=0, right=0;
        ll mid = (L+R)/2;
        if(cur->LC!=nullptr){
            left=query(cur->LC,L,mid,QL,QR);
        }
        if(cur->RC!=nullptr){
            right=query(cur->RC,mid+1,R,QL,QR);
        }
        return left + right;
    }
    public:
    SegmentTree(){
        root=Node(0);
        n=MAX;
    }
    ll query(ll L, ll R){
        return query(&root,0,n-1,L,R);
    }
    void update(ll p, ll d){
        update(&root,0,n-1,p,p,d);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<int> a(n);
    vector<int> b(n);
    unordered_map<int, int> order;
    for(int i = 0; i < n; i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b.begin(),b.end());
    for(int i = 0 ; i< n; i++){
        order[b[i]]=i;
    }
    SegmentTree st;
    ll swaps = 0;
    for(int i = 0; i < n; i++){
        swaps+=st.query(order[a[i]]+1,n-1);
        st.update(order[a[i]],1);
    }
    cout<<swaps<<"\n";
}