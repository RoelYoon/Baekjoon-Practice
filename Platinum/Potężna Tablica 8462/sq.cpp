#include <iostream>
#include <algorithm>
#include <cmath>
#define MAXL 100002
#define MAX 1000002
#define ll long long
using namespace std;
struct Query{
    int id;
    int L;
    int R;
    Query(){}
};
int nums[MAXL];
ll ans[MAXL];
Query qs[MAXL];
int freq[MAX]{};
ll power = 0;
void expand(int i){
    power-=(ll)freq[nums[i]]*(ll)freq[nums[i]]*(ll)nums[i];
    ++freq[nums[i]];
    power+=(ll)freq[nums[i]]*(ll)freq[nums[i]]*(ll)nums[i];
}
void shrink(int i){
    power-=(ll)freq[nums[i]]*(ll)freq[nums[i]]*(ll)nums[i];
    --freq[nums[i]];
    power+=(ll)freq[nums[i]]*(ll)freq[nums[i]]*(ll)nums[i];
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q,sqrtN; cin>>n>>q;
    sqrtN=sqrt(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    for(int i = 0; i < q; i++){
        cin>>qs[i].L>>qs[i].R;
        qs[i].id=i;
        --qs[i].L;    
        --qs[i].R;
    }
    sort(qs,qs+q,[sqrtN](const Query&a, const Query &b){
        if(a.L/sqrtN != b.L/sqrtN){
            return a.L < b.L;
        }else{
            return a.L/sqrtN%2 ? a.R > b.R : a.R < b.R;
        }
    });
    int L = 0, R = -1;
    for(int i = 0; i < q; i++){
        int QL=qs[i].L, QR=qs[i].R;
        while(L>QL){
            expand(--L);
        }
        while(R<QR){
            expand(++R);
        }
        while(L<QL){
            shrink(L++);
        }
        while(R>QR){
            shrink(R--);
        }
        ans[qs[i].id]=power;
    }
    for(int i = 0; i < q; i++)
        cout<<ans[i]<<"\n";
}