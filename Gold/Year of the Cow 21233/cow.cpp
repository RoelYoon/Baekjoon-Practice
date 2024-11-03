#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Bucket{
    int id;
    vector<int> nums;
    Bucket(){}
    Bucket(int id, int n):id(id){nums.push_back(n);}
    void insert(int n){
        nums.push_back(n);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    vector<int> pasts(n);
    for(int i = 0; i < n; ++i)
        cin>>pasts[i];
    sort(pasts.begin(),pasts.end(),greater<int>());
    vector<Bucket> buckets;
    buckets.emplace_back(pasts[0]/12+1,pasts[0]);
    for(int i = 1; i < n; ++i){
        int id = pasts[i]/12+1;
        if(id==buckets[buckets.size()-1].id){
            buckets[buckets.size()-1].insert(pasts[i]);
        }else{
            buckets.emplace_back(id,pasts[i]);
        }
    }
    vector<int> ds;
    for(int i = 0; i < buckets.size()-1; ++i){
        ds.push_back(buckets[i].id-buckets[i+1].id-1);
    }
    ds.push_back(buckets[buckets.size()-1].id-1);
    sort(ds.begin(),ds.end(),greater<int>());
    int minYears=pasts[0]/12+1;
    for(int i = 0; i < min(k-1,(int)ds.size()); ++i){
        minYears-=ds[i];
    }
    cout<<minYears*12<<"\n";
}
/*
2 2
10
40
*/ 
