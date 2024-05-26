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
    }
    void propagate(int p, int L, int R){
        if(lazyFlag[p]){
            st[p]=abs(((R-L)+1)-st[p]);
            if(L!=R){
                lazyFlag[LC(p)]=!lazyFlag[LC(p)];
                lazyFlag[RC(p)]=!lazyFlag[RC(p)];
            }else{
                data[L]=data[L]==0?1:0;
            }
            lazyFlag[p]=0;
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
        int left = query(LC(p),L,mid,QL,QR);
        int right = query(RC(p),mid+1,R,QL,QR);
        return left+right;
    }
    void update(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazyFlag[p]=!lazyFlag[p];
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR);
        update(RC(p),mid+1,R,QL,QR);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(vector<int> &a):n(a.size()),st(4*n),lazyFlag(4*n),data(a){
        build(0,0,n-1);
    }
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R){
        update(0,0,n-1,L,R);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m; cin>>n>>m;
    vector<int> lights(n);
    SegmentTree st(lights);
    for(int i = 0 ; i < m; i++){
        bool query;
        int L, R; 
        cin>>query>>L>>R; L--; R--;
        if(query){
            cout<<st.query(L,R)<<"\n";
        }else{
            st.update(L,R);
        }
    }
}
/*
.....
..###
##..#
5 4
0 3 5
0 1 4
0 3 4
1 1 5
*/