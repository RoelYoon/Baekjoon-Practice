#include <iostream>
#define MAX (246912)
using namespace std;
bool sieve[MAX+1]{};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 2; i <= MAX; ++i)
        if(!sieve[i])
            for(int j = i+i; j <= MAX; j+=i)
                sieve[j]=1;
    while(1){
        int n,cnt=0; cin>>n;
        if(!n) break;
        for(int i = n+1; i <= 2*n; ++i)
            cnt+=!sieve[i];
        cout<<cnt<<"\n";
    }
}