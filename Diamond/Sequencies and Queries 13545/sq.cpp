#include <iostream>
#include <cmath>
#include <algorithm>
#include <list>
#define MAX 100001
using namespace std;
struct Query{
    int id;
    int L;
    int R;
    Query(){}
};
int n;
int nums[MAX];
Query qs[MAX];
int ans[MAX];
list<int> dMap[MAX*2];
int freq[MAX*2]{};
int chunks[2005]{};
int query(){
    static const int sqrtN = sqrt(n*2)+1;
    for(int i = sqrtN-1; i>=0; --i){
        if(chunks[i]>0){
            const int a = (i+1)*sqrtN-1;
            const int b = i*sqrtN;
            for(int j = 2*n-1 < a ? 2*n-1 : a; j>=b ;--j){
                if(freq[j]>0){
                    return j;
                }
            }
        }
    }
    return 0;
}
void update(int p, int u){
    static const int sqrtN = sqrt(2*n)+1;
    if(p<0){
        p*=-1;
        p+=MAX;
    }
    freq[p]+=u;
    chunks[p/sqrtN]+=u;
}
void expand(bool L, int i){
    list<int> &dq = dMap[nums[i] < 0 ? (nums[i]*-1)+MAX : nums[i]];
    if(!dq.empty())
        update(dq.back() - dq.front(),-1);
    L ? dq.push_front(i) : dq.push_back(i);
    update(dq.back() - dq.front(),1);
}
void shrink(bool L,int i){
    list<int> &dq = dMap[nums[i] < 0 ? (nums[i]*-1)+MAX : nums[i]];
    update(dq.back() - dq.front(),-1);
    if(!dq.empty()){
        L ? dq.pop_front() : dq.pop_back();
        update(dq.back() - dq.front(),1);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n; ++n;
    const int s = sqrt(n);
    int a[MAX];
    a[0]=0;
    for(int i = 1; i < n; i++)
        cin>>a[i];
    nums[0]=a[0];
    nums[1]=a[1];
    for(int i = 1; i < n; i++)
        nums[i]=nums[i-1]+a[i];
    int q; cin>>q;
    for(int i = 0; i < q; i++){
        cin>>qs[i].L>>qs[i].R;
        qs[i].id=i;
        qs[i].L--;
    }
    sort(qs,qs+q,[s](const Query&a, const Query&b){
        const int as = a.L/s;
        if(as != b.L/s){
            return a.L < b.L;
        }else{
            return as%2 ? a.R > b.R : a.R < b.R;
        }
    });
    int L = 0, R=-1;
    for(int i = 0; i < q; i++){
        const int QL = qs[i].L, QR=qs[i].R;
        while(R<QR)
            expand(0,++R);
        while(L>QL)
            expand(1,--L);
        while(R>QR){
            shrink(0,R--);
        }
        while(L<QL){
            shrink(1,L++);
        }
        ans[qs[i].id]=query();
        if(QL==1 && QR==n-1 && nums[n-1]==0){ans[qs[i].id]=n-1;}
    }
    for(int i = 0; i < q; i++)
        cout<<ans[i]<<"\n";
}