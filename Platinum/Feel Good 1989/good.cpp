#include <iostream>
#include <vector>
#define ll long long
using namespace std;
struct QueryPair{
    ll sum;
    int min;
    int minPos;
    ll val;
    QueryPair(ll s, int m, int mp):sum(s),min(m),minPos(mp),val(sum*(ll)min){}
};
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    #define INF 1000000000
    private:
    int n;
    vector<ll> data;
    vector<ll> stSum;
    vector<ll> stMin;
    vector<ll> stMinPos;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void build(int p, int L, int R){
        if(L==R){
            stSum[p]=data[L];
            stMin[p]=data[L];
            stMinPos[p]=L;
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid);
        build(RC(p),mid+1,R);
        stSum[p]=stSum[LC(p)]+stSum[RC(p)];
        stMin[p]=min(stMin[LC(p)],stMin[RC(p)]);
        stMinPos[p]=stMin[p]==stMin[LC(p)] ? stMinPos[LC(p)] : stMinPos[RC(p)];
    }
    QueryPair query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return QueryPair(0,INF,0);
        }
        if(inBounds(L,R,QL,QR)){
            return QueryPair(stSum[p],stMin[p],stMinPos[p]);
        }
        int mid = (L+R)/2;
        QueryPair left = query(LC(p),L,mid,QL,QR);
        QueryPair right = query(RC(p),mid+1,R,QL,QR);
        QueryPair returnVal = QueryPair(left.sum+right.sum,min(left.min,right.min),(min(left.min,right.min)==left.min?left.minPos : right.minPos));
        return returnVal;
    }
    public:
    SegmentTree(vector<ll> &a):n(a.size()),data(a),stSum(4*n),stMin(4*n,INF),stMinPos(4*n){build(0,0,n-1);};
    QueryPair query(int L, int R){
        return query(0,0,n-1,L,R);
    }
};
ll bestDay = 0;
int bestL=1, bestR=1;
ll DC(int L, int R, SegmentTree &st){
    if(L>R){return 0;}
    if(L==R){
        ll v = st.query(L,R).val;
        if(v>bestDay){
            bestDay=v;
            bestL=L+1;
            bestR=R+1;
        }
    }
    QueryPair qp = st.query(L,R);
    ll cur = qp.val;
    if(cur>bestDay){
        bestDay=cur;
        bestL=L+1;
        bestR=R+1;
    }
    int pivot = qp.minPos;
    ll left = DC(L,pivot-1,st);
    ll right = DC(pivot+1,R,st);
    return max(cur,max(left,right));
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<ll> days(n);
    for(int i = 0; i < n; i++){
        cin>>days[i];
    }
    if(n==1){cout<<days[0]<<"\n"<<"1 1\n"; return 0;}
    SegmentTree st(days);
    DC(0,n-1,st);
    cout<<bestDay<<"\n";
    cout<<bestL<<" "<<bestR<<"\n";
}