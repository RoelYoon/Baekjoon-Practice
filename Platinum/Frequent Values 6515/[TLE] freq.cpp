#define TIME
#ifdef TEST
    #define INPUT freopen("test","r",stdin);
#else
    #define INPUT 
#endif
#ifdef TIME
    #include <time.h>
    #define START clock_t start=clock();
    #define END clock_t end=clock(); \
    printf("%f",(double)(end-start)/CLOCKS_PER_SEC);
#else
    #define START
    #define END
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int st[400004]{};
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]+=u;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=max(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(int n):n(n){}
    int query(){
        return st[0];
    }
    void update(int P, int U){
        update(0,0,n-1,P,P,U);
    }
};
struct Query{
    int L, R, id;
    Query(){}
};
int main(){
    START
    INPUT
    int arr[100000],zip[100000],leftBound[100000],rightBound[100001],ans[100000];
    Query queries[100000];
    while(1){
        int n,q,s; scanf("%d",&n);
        if(!n) break;
        scanf("%d",&q);
        s = sqrt(n);
        for(int i = 0; i < n; ++i)
            scanf("%d",&arr[i]),zip[i]=arr[i];
        int* zipEnd = unique(zip,zip+n);
        int type = 100000;
        for(int i = 0; i < n; ++i){
            arr[i]=lower_bound(zip,zipEnd,arr[i])-zip;
            if(arr[i]!=type){
                rightBound[type]=i-1;
                type=arr[i];
                leftBound[type]=i;
            }
        }rightBound[type]=n-1;
        SegmentTree st(100001);
        for(int i = 0; i < q; ++i){
            scanf("%d%d",&queries[i].L,&queries[i].R);
            --queries[i].L,--queries[i].R;
            queries[i].id=i;
        }
        sort(queries,queries+q,[s](const Query &a, const Query &b){
            const int as = a.L/s;
            if(as != b.L/s) return a.L<b.L;
            return as%2 ? a.R>b.R : a.R<b.R;
        });
        int L=0,R=-1;
        for(int i = 0; i < q; ++i){
            const int QL=queries[i].L, QR=queries[i].R;
            while(L>QL){
                int v=arr[L-1];
                int bound = max(leftBound[v],QL);
                st.update(v,abs(L-bound));
                L=bound;
            }
            while(R<QR){
                int v=arr[R+1];
                int bound = min(rightBound[v],QR);
                st.update(v,abs(R-bound));
                R=bound;
            }
            while(L<QL){
                int v=arr[L];
                int bound = min(rightBound[v],QL-1);
                st.update(v,-(abs(L-bound)+1));
                L=bound+1;
            }
            while(R>QR){
                int v=arr[R];
                int bound = max(leftBound[v],QR+1);
                st.update(v,-(abs(R-bound)+1));
                R=bound-1;
            }
            ans[queries[i].id] = st.query();
        }
        for(int i = 0; i < q; ++i)
            printf("%d\n",ans[i]);
    }
    END
}