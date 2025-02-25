#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
class SqrtDecompositon{
    int n;
    const int s = 316;
    int freqFreq[100001]{},chunks[317]{};
    public:
    SqrtDecompositon(){};
    void update(int p, int u){
        freqFreq[p]+=u;
        chunks[p/s]+=u;
    }
    int query(){
        for(int i = s; i>=0; --i){
            if(chunks[i]){
                for(int j = (i+1)*s-1; j >= i*s; --j){
                    if(freqFreq[j])
                        return j;
                }
            }
        }
        return 0;
    }
};
struct Query{
    int L, R, id;
    Query(){}
};
int main(){
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
        SqrtDecompositon sqd;
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
        int numFreq[100001]{};
        int L=0,R=-1;
        for(int i = 0; i < q; ++i){
            const int QL=queries[i].L, QR=queries[i].R;
            while(L>QL){
                int v=arr[L-1];
                int bound = max(leftBound[v],QL);
                if(numFreq[v])
                    sqd.update(numFreq[v],-1);
                numFreq[v]+=abs(L-bound);
                sqd.update(numFreq[v],1);
                L=bound;
            }
            while(R<QR){
                int v=arr[R+1];
                int bound = min(rightBound[v],QR);
                if(numFreq[v])
                    sqd.update(numFreq[v],-1);
                numFreq[v]+=abs(R-bound);
                sqd.update(numFreq[v],1);
                R=bound;
            }
            while(L<QL){
                int v=arr[L];
                int bound = min(rightBound[v],QL-1);
                if(numFreq[v])
                    sqd.update(numFreq[v],-1);
                numFreq[v]-=(abs(L-bound)+1);
                sqd.update(numFreq[v],1);
                L=bound+1;
            }
            while(R>QR){
                int v=arr[R];
                int bound = max(leftBound[v],QR+1);
                if(numFreq[v])
                    sqd.update(numFreq[v],-1);
                numFreq[v]-=(abs(R-bound)+1);
                sqd.update(numFreq[v],1);
                R=bound-1;
            }
            ans[queries[i].id] = sqd.query();
        }
        for(int i = 0; i < q; ++i)
            printf("%d\n",ans[i]);
    }
}
/*
5 3
-3 -1 0 1 2
1 5
1 1
2 5
5 3
0 0 0 0 0
1 5
1 2
2 4
0

1
1
1
5
2
3

10 3
-1 -1 1 1 1 1 3 10 10 10
6 8
10 10
5 5
0

Ans:
1
1
1
*/