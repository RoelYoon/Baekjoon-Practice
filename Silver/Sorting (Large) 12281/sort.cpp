#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    for(int t = 0; t < T; ++t){
        int n; cin>>n;
        vector<int> ans(n),order(n);
        vector<int> sortedE,sortedO;
        for(int i = 0; i < n; ++i){
            int x; cin>>x;
            if(x%2){
                sortedO.push_back(x);
            }else{
                sortedE.push_back(x);
            }
            order[i] = x;
        }
        sort(sortedO.begin(), sortedO.end());
        sort(sortedE.begin(), sortedE.end(), [](const int &a, const int &b){
            return a>b;
        });
        int a=0,b=0;
        while(a<sortedO.size() && b<sortedE.size()){
            if(order[a+b]%2){
                ans[a+b] = sortedO[a];
                ++a;
            }else{
                ans[a+b] = sortedE[b];
                ++b;
            }
        }
        while(a<sortedO.size()){
            ans[a+b] = sortedO[a];
            ++a;
        }
        while(b<sortedE.size()){
            ans[a+b] = sortedE[b];
            ++b;
        }
        cout<<"Case #"<<t+1<<": ";
        for(int i = 0; i < n; ++i){
            cout<<ans[i]<<(i==n-1?"\n":" ");
        }
    }
}