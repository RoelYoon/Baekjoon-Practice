#include <iostream>
#define MAX 1000000
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int DP[MAX+1];
    DP[1]=0;
    DP[2]=DP[3]=1;
    int n; cin>>n;
    for(int i = 4; i <= n; ++i){
        DP[i]=1e9;
        if(!(i%3))
            DP[i]=DP[i/3]+1;
        if(!(i%2))
            DP[i]=min(DP[i],DP[i/2]+1);
        DP[i]=min(DP[i],DP[i-1]+1);
    }
    cout<<DP[n]<<"\n";
}
