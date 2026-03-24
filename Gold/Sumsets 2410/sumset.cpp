#include <iostream>
#define ll long long
using namespace std;
const ll M = ((ll)1e9);
int pa[21];
ll DP[1000001]{};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    pa[0]=1;
    for(int p = 1; p <= 20; ++p)
        pa[p] = pa[p-1]*2;
    DP[0]=1;
    int n; cin>>n;
    for(int p = 0; p <= 20; ++p){
        for(int i = 1; i <= n; ++i){
            if(i-pa[p]>=0)
            DP[i]=(DP[i]+DP[i-pa[p]])%M;
        }
    }
    cout<<DP[n]<<"\n";
}