#include <iostream>
using namespace std;
int DP[1000]{};
int a[1000];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i=0;i<n;++i){
        cin>>a[i];
        DP[i]=1;
    }
    for(int i = 1; i < n; ++i){
        for(int j = 0; j < i; ++j){
            if(a[j]<a[i]){
                DP[i] = max(DP[i],DP[j]+1);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; ++i)
        ans = max(ans,DP[i]);
    cout<<ans<<"\n";
}