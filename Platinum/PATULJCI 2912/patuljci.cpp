#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAXN 300001
#define MAXQ 10001
using namespace std;
struct Query{
    int id;
    int L;
    int R;
    Query(){}
};
int n, c, q, sqrtN; 
int dt[MAXQ];
int chunks[1000];
int nums[MAXN];
int ans[MAXQ]{};
Query qs[MAXQ];
int freq[MAXQ]{};
int query(int L, int R){
    const int d = (R-L+1)/2;
    for(int i = 1; i <= c; i++)
        if(dt[i]>d)
            return i;
    return -1;
}
void expand(int i){
    ++dt[nums[i]];
}
void shrink(int i){
    --dt[nums[i]];
}
int main(){
    scanf("%d%d",&n,&c);
    sqrtN = sqrt(n);
    for(int i = 0; i < n; ++i)
        scanf("%d",&nums[i]);
    scanf("%d",&q);
    for(int i = 0; i < q; ++i){
        scanf("%d%d",&qs[i].L,&qs[i].R);
        qs[i].id=i;
        --qs[i].L; --qs[i].R;
    }
    sort(qs,qs+q,[](const Query&a, const Query&b){
        if(a.L/sqrtN != b.L/sqrtN){
            return a.L<b.L;
        }else{
            return a.L/sqrtN%2 ? a.R > b.R : a.R < b.R;
        }
    });
    int L=0, R=-1;
    for(int i = 0; i < q; ++i){
        const int QL = qs[i].L, QR = qs[i].R;
        while(L > QL)
            expand(--L);
        while(R < QR)
            expand(++R);
        while(L < QL)
            shrink(L++);
        while(R > QR)
            shrink(R--);
        const int d = query(QL,QR);
        if(d!=-1)
            ans[qs[i].id]=d;
    }
    for(int i = 0; i < q; ++i){
        if(ans[i]>0){
            printf("yes %d\n",ans[i]);
        }else{
            printf("no\n");
        }
    }
}