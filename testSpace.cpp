#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
class SegmentTree{
    #define P(i) (((i)-1)/2)
    #define LC(i) ((i)*2 + 1)
    #define RC(i) ((i)*2 + 2)
    private:
    int n;
    vector<int> &data;
    vector<int> st;
    vector<bool> lazyFlag;
    vector<int> lazyUpdate;
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
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    inline int appliedUpdate(int p, int L, int R){
        return st[p] + lazyUpdate[p] * ((R-L)+1);
    }
    void propagate(int p, int L, int R){
        if(lazyFlag[p]){
            st[p] = appliedUpdate(p,L,R);
            if(L!=R){
                lazyFlag[LC(p)]=lazyFlag[RC(p)]=1;
                lazyUpdate[LC(p)]+=lazyUpdate[p];
                lazyUpdate[RC(p)]+=lazyUpdate[p];
            }else{
                data[p]+=lazyUpdate[p];
            }
            lazyFlag[p]=0;
            lazyUpdate[p]=0;
        }
    }
    int query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        int leftQ = query(LC(p), L, mid, QL, QR);
        int rightQ = query(RC(p), mid+1, R, QL, QR);
        return leftQ+rightQ;
    }
    void update(int p, int L, int R, int QL, int QR, int updateVal){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)) return;
        if(inBounds(L,R,QL,QR)){
            lazyFlag[p]=1;
            lazyUpdate[p]=updateVal;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,updateVal);
        update(RC(p),mid+1,R,QL,QR,updateVal);
        int left = st[LC(p)];
        int right = st[RC(p)];
        st[p]=left+right;
    }
    public:
    SegmentTree(vector<int> &data):n(data.size()),st(4*data.size()),lazyFlag(4*data.size()),lazyUpdate(4*data.size()),data(data){
        build(0,0,n-1);
    }
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, int updateVal){
        update(0,0,n-1,L,R,updateVal);
    }
    void printData(){
        for(int i = 0; i < n; i++){
            cout<<data[i]<<" ";
        }cout<<"\n";
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    srand(time(0));
    freopen("testSpace.out","w",stdout);
    int n = 100000; int k = 100000;
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i < n; i++){
        cout<<rand()%100000+1<<" ";
    }cout<<"\n";
    int q = 100000;
    cout<<q<<"\n";
    for(int i = 0; i < q; i++){
        int a = rand()%100000+1;
        int b = rand()%100000+1;
        if(a>b){
            int temp = a;
            a = b;
            b = temp;
        }
        cout<<a<<" "<<b<<"\n";
    }
}