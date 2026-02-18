#include <iostream>
#define ll long long
#define MAX_N 1000000
using namespace std;
ll sieve[MAX_N+1]{};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int x = 5; x <= MAX_N; x*=5){
        for(int i = x; i <= MAX_N; i+=x){
            sieve[i]++;
        }
    };
    int t = 1;
    while(1){
        int n; cin>>n;
        if(!n) break;
        ll ans = 0;
        for(int i = 0; i <= n; ++i){
            ans+=sieve[i];
        } 
        cout<<"Case #"<<t++<<": "<<ans<<"\n";
    }
}
