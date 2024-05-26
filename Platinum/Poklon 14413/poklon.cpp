#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#define MAX 500000
#define ll long long
using namespace std;
struct Query{
    int id;
    int a;
    int b; 
    Query(){}  
};
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    int nums[MAX];
    int orderedNums[MAX];
    Query qs[MAX];
    int ans[MAX];
    int map[MAX]{};
    unordered_map<int, int> compressed;
    int n,q; cin>>n>>q;
    const int s = sqrt(n);
    for(int i = 0; i < n ; i++){
        cin>>nums[i];
        orderedNums[i]=nums[i];
    }
    sort(orderedNums,orderedNums+n);
    for(int i = 0; i < n; i++)
        compressed[orderedNums[i]]=i;
    for(int i = 0; i < n; i++)
        nums[i]=compressed[nums[i]];
    for(int i = 0; i < q; i++){
        cin>>qs[i].a>>qs[i].b;
        qs[i].a--; qs[i].b--;
        qs[i].id=i;
    }
    sort(qs,qs+q,[s](const Query&a, const Query &b){
        if(a.a/s != b.a/s){return a.a<b.a;} 
        else{return a.a/s % 2 ? a.b>b.b : a.b<b.b;}
    });
    int L = 0;
    int R = -1;
    int size = 0;
    for(int i = 0; i < q; i++){
        const int QL = qs[i].a, QR = qs[i].b;
        while(L > QL){
            if(++map[nums[--L]]==2){++size;}
            else if(map[nums[L]]==3){--size;}
        }
        while(R < QR){
            if(++map[nums[++R]]==2){++size;}
            else if(map[nums[R]]==3){--size;}
        }
        while(L < QL){
            if(--map[nums[L]]==2){++size;}
            else if(map[nums[L]]==1){--size;}
            ++L;
        }
        while(R > QR){
            if(--map[nums[R]]==2){++size;}
            else if(map[nums[R]]==1){--size;}
            --R;
        }
        ans[qs[i].id]=size;
    }
    for(int i = 0; i < q; i++)
        cout<<ans[i]<<"\n";
}