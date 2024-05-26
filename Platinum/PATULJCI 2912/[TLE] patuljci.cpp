/*
Optimal time complexity, but TLEs due to higher constant
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#define MAXN 300001
#define MAXQ 10001
using namespace std;
struct Query{
    int id;
    int L;
    int R;
    Query(){}
};
struct Data{
    int count;
    unordered_set<int> nums;
    Data():count(0){}
};
int n, c, q, sqrtN; 
Data dt[MAXN];
int chunks[1000];
int nums[MAXN];
int ans[MAXQ]{};
Query qs[MAXQ];
int freq[MAXQ]{};
int query(){
    for(int i = sqrtN; i >= 0; --i){
        if(chunks[i]>0){
            const int e=i*(sqrtN+1);
            for(int j = min(n,(i+1)*(sqrtN+1)); j >= e; --j){
                if(dt[j].count>0){
                    return j;
                }
            }
        }
    }
    return -1;
}
void update(int p, int u){
    const static int s = sqrtN+1;
    dt[p].count+=u;
    chunks[p/s]+=u;
}
void expand(int i){
    int &f = freq[nums[i]];
    if(dt[f].count>0){
        update(f,-1);
        dt[f].nums.erase(nums[i]);
    }
    ++f;
    update(f,1);
    dt[f].nums.insert(nums[i]);
}
void shrink(int i){
    int &f = freq[nums[i]];
    if(dt[f].count>0){
        update(f,-1);
        dt[f].nums.erase(nums[i]);
    }
    --f;
    update(f,1);
    dt[f].nums.insert(nums[i]);
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
        const int d = query();
        if(d!=-1 && d > (R-L+1)/2)
            ans[qs[i].id]=*dt[d].nums.begin();
    }
    for(int i = 0; i < q; ++i){
        if(ans[i]>0){
            printf("yes %d\n",ans[i]);
        }else{
            printf("no\n");
        }
    }
}