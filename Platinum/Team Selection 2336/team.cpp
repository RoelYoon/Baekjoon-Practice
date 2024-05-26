#include <cstdio>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(i) (2*(i)+1)
    #define RC(i) (2*(i)+2)
    #define INF 1000000000
    private:
    int n;
    vector<int> st; 
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int query(int p,int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return INF;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        int left = query(LC(p),L,mid,QL,QR);
        int right = query(RC(p),mid+1,R,QL,QR);
        return min(left,right);
    }
    void update(int p, int L, int R, int QL, int QR, int d){
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
        st[p] = min(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(int n):n(n),st(4*n,INF){}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int p, int d){
        update(0,0,n-1,p,p,d);
    }
};
int main(){
    int n; scanf("%d",&n);
    vector<vector<int>> comp(3,vector<int>(n));
    for(int i = 0 ; i < 3; i++){
        for(int j = 0; j < n; j++){
            scanf("%d",&comp[i][j]); comp[i][j]--;
        }
    }
    vector<vector<int>> ranks(3,vector<int>(n));
    for(int i = 0; i < 3; i++){
        vector<int> &v = comp[i];
        for(int j = 0; j < n; j++){
            ranks[i][v[j]]=j;
        }
    }
    SegmentTree st2(n);
    //s1 as base
    int count = 0;
    for(int i = 0; i < n; i++){
        int &f = comp[0][i]; int &fr = ranks[0][f];
        int &sr = ranks[1][f];
        int &tr = ranks[2][f];
        if(st2.query(0,sr) > tr){
            ++count;
        }
        st2.update(sr,tr);
    }
    printf("%d\n",count);
}
/*
3
1 3 2 
1 2 3
3 2 1 
*/