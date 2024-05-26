#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#define MAX 100005
using namespace std;
struct Query{
    int id;
    int L;
    int R;
    Query(){}
};
int n;
void expand(int nums[MAX],int num2Count[MAX],map<int, int> &countSet, int i){
    if(i<0 || i>=n){return;}
    map<int, int>::iterator p = countSet.find(num2Count[nums[i]]);
    if(p==countSet.end()){
        ++num2Count[nums[i]];
        ++countSet[num2Count[nums[i]]];
    }else{
        --p->second;
        if(p->second==0){countSet.erase(p);}
        ++num2Count[nums[i]];
        ++countSet[num2Count[nums[i]]];
    }
}
void shrink(int nums[MAX],int num2Count[MAX],map<int, int> &countSet, int i){
    if(i<0 || i>=n){return;}
    map<int, int>::iterator p = countSet.find(num2Count[nums[i]]);
    if(p==countSet.end()){
        --num2Count[nums[i]];
        ++countSet[num2Count[nums[i]]];
    }else{
        --p->second;
        if(p->second==0){countSet.erase(p);}
        --num2Count[nums[i]];
        ++countSet[num2Count[nums[i]]];
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    const int s = sqrt(n);
    int nums[MAX]{};
    for(int i = 0; i < n; i++)
        cin>>nums[i];
    int q; cin>>q;
    Query qs[MAX];
    int ans[MAX]{};
    for(int i = 0; i < q; i++){
        cin>>qs[i].L>>qs[i].R; 
        qs[i].id=i;
        --qs[i].L;
        --qs[i].R;
    }
    sort(qs,qs+q,[s](const Query&a, const Query&b){
        if(a.L/s != b.L/s){
            return a.L < b.L;
        }else{
            //same chunk
            return a.L/s%2 ? a.R > b.R : a.R < b.R;
        }
    });
    map<int, int> countSet; //ordered by count
    int num2Count[MAX]{};
    int L = 0, R = -1;
    for(int i = 0; i < q; i++){
        int QL = qs[i].L, QR = qs[i].R;
        while(L>QL){
            expand(nums,num2Count,countSet,--L);
        }
        while(R<QR){
            expand(nums,num2Count,countSet,++R);
        }
        while(L<QL){
            shrink(nums,num2Count,countSet,L++);
        }
        while(R>QR){
            shrink(nums,num2Count,countSet,R--);
        }
        if(countSet.empty()){continue;}
        ans[qs[i].id]=countSet.rbegin()->first;
    }
    for(int i = 0; i < q; i++)
        cout<<ans[i]<<"\n";
}
/*
5
100000 100000 100000 100000 100000
1
2 5
*/