#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
using namespace std;
struct Query{
    int id;
    int a;
    int b; 
    Query(){}  
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    const int s = sqrt(n);
    int nums[100000];
    for(int i = 0; i < n ; i++)
        cin>>nums[i];
    int q; cin>>q;
    Query qs[100000];
    int ans[100000];
    for(int i = 0; i < q; i++){
        cin>>qs[i].a>>qs[i].b; qs[i].a--; qs[i].b--;
        qs[i].id=i;
    }
    sort(qs,qs+q,[&s](const Query&a, const Query &b){
        if(a.a/s != b.a/s){return a.a<b.a;} 
        else{return a.a/s % 2 ? a.b<b.b : a.b>b.b;}
    });
    int L = 0;
    int R = -1;
    unordered_map<int,int> map; 
    for(int i = 0; i < q; i++){
        int &QL = qs[i].a;
        int &QR = qs[i].b;
        while(L > QL){
            ++map[nums[--L]];
        }
        while(R < QR){
            ++map[nums[++R]];
        }
        while(L < QL){
            if(--map[nums[L]]<=0){map.erase(nums[L]);};
            ++L;
        }
        while(R > QR){
            if(--map[nums[R]]<=0){map.erase(nums[R]);};
            --R;
        }
        ans[qs[i].id]=map.size();
    }
    for(int i = 0; i < q; i++)
        cout<<ans[i]<<"\n";
}