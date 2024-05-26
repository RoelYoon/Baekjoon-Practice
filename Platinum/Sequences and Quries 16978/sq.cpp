#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    private:
    int n;
    vector<ll> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void build(int p, int L, int R,vector<ll> &data){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=st[LC(p)]+st[RC(p)];
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
    public:
    SegmentTree(vector<ll> &data):n(data.size()),st(4*n){build(0,0,n-1,data);}
    ll query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int p, ll d){
        update(0,0,n-1,p,p,d);
    }
};
struct Query{
    int order;
    int i;
    int j;
    int k;
    Query(int i, int j, int k, int order):i(i),j(j),k(k),order(order){}
};
struct Update{
    int i;
    int d;
    Update(int i, int d):i(i),d(d){}
};
struct Answer{
    int order;
    ll ans;
    Answer(int order, ll ans):order(order),ans(ans){}
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin>>n;
    vector<ll> nums(n);
    for(int i = 0 ; i < n; i++)
        cin>>nums[i];
    SegmentTree st(nums);
    vector<Query> queries;
    vector<Update> updates;
    cin>>q;
    for(int i = 0; i < q; i++){
        int t; cin>>t;
        if(t==1){
            int a,b; cin>>a>>b; a--;
            updates.emplace_back(a,b);
        }else{
            int k,a,b; cin>>k>>a>>b; a--; b--;
            queries.emplace_back(a,b,k,i);
        }
    }
    int UP = 0;
    sort(queries.begin(),queries.end(),[](const Query &a, const Query &b){return a.k<b.k;});
    vector<Answer> answers;
    for(int i = 0; i < queries.size(); i++){
        while(UP<updates.size() && UP<queries[i].k){
            st.update(updates[UP].i,updates[UP].d);
            ++UP;
        }
        answers.emplace_back(queries[i].order,st.query(queries[i].i,queries[i].j));
    }
    sort(answers.begin(),answers.end(),[](const Answer &a, const Answer &b){return a.order<b.order;});
    for(int i = 0; i < answers.size(); i++)
        cout<<answers[i].ans<<"\n";
}