#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#define MAX 100005
using namespace std;
struct Query{
    int id;
    int L;
    int R;
    Query(){}
};
class SqrtArray{
    int chunks[5005]{};
    int freq[MAX]{};
    int n;
    int s;
    public:
    //sqrt(n)+1 because 1-based array
    SqrtArray(int n):n(n),s(sqrt(n)+1){}
    int query(){
        for(int i = s; i >= 0; --i){
            if(chunks[i]==0){continue;}
            for(int j = min((i+1)*s-1,n-1); j >= i*s; --j){
                if(freq[j]>0)
                    return j;
            }
        }
        return 0;
    }
    void update(int d, int u){
        freq[d]+=u;
        chunks[d/s]+=u;
    }
};
list<int> lists[MAX*10];
int pf[MAX];
void expand(bool L, int p, SqrtArray& sa){
    list<int> &dq = lists[pf[p]];
    if(!dq.empty())
        sa.update(dq.back()-dq.front(),-1);
    L ? dq.push_front(p) : dq.push_back(p);
    sa.update(dq.back()-dq.front(),1);
}
void shrink(bool L, int p, SqrtArray& sa){
    list<int> &dq = lists[pf[p]];
    sa.update(dq.back()-dq.front(),-1);
    if(!dq.empty()){
        L ? dq.pop_front() : dq.pop_back();
        sa.update(dq.back()-dq.front(),1);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k,q; cin>>n>>k;
    const int s = sqrt(n);
    int data[MAX];
    for(int i = 1; i <= n; ++i){
        cin>>data[i];
    }
    data[0]=pf[0]=0;
    for(int i = 1; i <= n; ++i){
        pf[i]=((data[i]%k)+(pf[i-1]%k))%k;
    }
    cin>>q;
    Query queries[MAX];
    int ans[MAX];
    for(int i = 0; i < q; ++i){
        cin>>queries[i].L>>queries[i].R;
        --queries[i].L;
        queries[i].id=i;
    }
    sort(queries,queries+q,[s](Query &a, Query &b){
        if(a.L/s != b.L/s) return a.L < b.L;
        return a.L/s%2 ? a.R > b.R : a.R < b.R;
    });
    int L = 0, R = -1;
    SqrtArray sa(n);
    for(int i = 0; i < q; ++i){
        int QL = queries[i].L, QR = queries[i].R;
        while(L > QL){
            expand(1,--L,sa);
        }
        while(R < QR){
            expand(0,++R,sa);
        }
        while(L < QL){
            shrink(1,L++,sa);
        }
        while(R > QR){
            shrink(0,R--,sa);
        }
        ans[queries[i].id]=sa.query();
    }
    for(int i = 0; i < q; ++i){
        cout<<ans[i]<<"\n";
    }
}