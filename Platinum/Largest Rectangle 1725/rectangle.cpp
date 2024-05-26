#include <iostream>
#include <vector>
#define ll long long
#define INF 1000000000000
using namespace std;
inline ll size(int L, int R){
    return (R-L)+1;
}
struct Rectangle{
    ll h;
    int pos;
    Rectangle(ll h, int i):h(h),pos(i){}
    Rectangle():h(INF){}
};
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    #define P(i) (((i)-1)/2)
    private:
    int n;
    vector<ll> data;
    vector<Rectangle> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void build(int p, int L, int R){
        if(L==R){
            st[p]=Rectangle(data[L],L);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid);
        build(RC(p),mid+1,R);
        st[p]=st[LC(p)].h < st[RC(p)].h ? st[LC(p)] : st[RC(p)];
    }
    Rectangle query(int p, int L, int R, int QL, int QR){
        //min height query
        if(outBounds(L,R,QL,QR)){
            return Rectangle();
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        Rectangle leftH = query(LC(p),L,mid,QL,QR);
        Rectangle rightH = query(RC(p),mid+1,R,QL,QR);
        return leftH.h < rightH.h ? leftH : rightH;
    }
    public:
    SegmentTree(){}
    SegmentTree(vector<ll> &a):n(a.size()),st(4*a.size()),data(a){
        build(0,0,n-1);
    }
    Rectangle query(int L, int R){
        return query(0,0,n-1,L,R);
    }
};
ll DC(int L, int R, SegmentTree &st){
    if(L>R){return 0;}
    Rectangle minRec = st.query(L,R);
    if(L==R){return minRec.h;}
    ll width = size(L,R);
    ll maxArea = minRec.h * width;
    int pivot = minRec.pos;
    ll leftMaxArea = DC(L,pivot-1,st);
    ll rightMaxArea = DC(pivot+1,R,st);
    return max(maxArea, max(leftMaxArea,rightMaxArea));
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<ll> h(n);
    for(int i = 0; i < n; i++){
        cin>>h[i];
    }
    SegmentTree st(h);
    ll maxArea = DC(0,n-1,st);
    cout<<maxArea<<"\n";
}