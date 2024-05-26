#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    private:
    int n;
    vector<int> st;
    vector<int> data;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L,int R, int QL, int QR){
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
        st[p]=st[LC(p)]+st[RC(p)];
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
            data[L]=uVal;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,uVal);
        update(RC(p),mid+1,R,QL,QR,uVal);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(vector<int> &a):n(a.size()),data(a),st(4*n){build(0,0,n-1);}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int P, int uVal){
        update(0,0,n-1,P,P,uVal);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n,m; cin>>n>>m;
        vector<int> movies(n+m,0);
        int head = m-1;
        vector<int> pos(n);
        for(int i = m; i < n+m; i++){
            movies[i]=1;
            pos[i-m]=i;
        }
        SegmentTree st(movies);
        for(int i = 0; i < m; i++){
            int q; cin>>q; q--;
            cout<<(st.query(0,pos[q])-1)<<" ";
            st.update(head,1);
            st.update(pos[q],0);
            pos[q]=head;
            head--;
        }cout<<"\n";
    }
}