#include <iostream>
#include <vector>
#include <unordered_map>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    for(int t = 1; t <= T; ++t){
        int n; cin>>n;
        vector<ll> nums(n*2);
        unordered_map<ll,vector<int>> map;
        for(int i = 0; i < n*2; ++i){
            cin>>nums[i];
            map[nums[i]].push_back(i);
        }
        vector<ll> prices;
        for(int i = 0; i < n*2; ++i){
            unordered_map<ll,vector<int>>::iterator it = map.find(nums[i]*4/3);
            if(it!=map.end()){
                nums[(it->second).back()]=0;
                (it->second).pop_back();
                if(it->second.empty())
                    map.erase(it);
                prices.push_back(nums[i]);
            }
        }
        cout<<"Case #"<<t<<": ";
        for(int i = 0; i < n; ++i)
            cout<<prices[i]<<" ";
        cout<<"\n";
    }
}