#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    long long ans = 0;
    int p = -1;
    for(int i = 0; i < n; ++i){
        int x; cin>>x;
        if(p==-1) p = x;
        ans+=(long long)(x-p)*(long long)(x-p);
        p = x;
    }
    cout<<ans<<"\n";
}