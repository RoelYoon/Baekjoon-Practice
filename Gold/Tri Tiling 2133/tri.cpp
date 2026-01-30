#include <iostream>
#define ll long long
using namespace std;
ll DP[31];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    if(n%2){
        cout<<"0\n";
        return 0;
    }
    DP[0]=1;
    DP[2]=3;
    for(int i = 4; i <= n; i+=2){
        DP[i]=4*DP[i-2]-DP[i-4];
    }
    cout<<DP[n]<<"\n";
}