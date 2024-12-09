#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    bool sieve[10000];
    int cnt = 0;
    for(int i = 2; i <= n; ++i){
        for(int j = i; j <= n; j+=i){
            if(!sieve[j]){
                sieve[j]=1;
                cnt++;
                if(cnt==k){
                    cout<<j<<"\n";
                    return 0;
                }
            }
        }
    }
}