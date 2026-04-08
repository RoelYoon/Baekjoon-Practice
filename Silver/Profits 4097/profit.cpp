#include <iostream>
#define INF ((int)1e9)
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        int n; cin>>n;
        if(!n) break;
        int mx = -INF;
        int cur = 0;
        while(n--){
            int p; cin>>p;
            cur+=p;
            mx = max(mx, cur);
            cur = max(cur,0);
        }
        cout<<mx<<"\n";
    }
}