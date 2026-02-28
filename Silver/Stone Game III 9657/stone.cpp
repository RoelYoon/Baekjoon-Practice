#include <iostream>
using namespace std;
bool DP[1001]; // 1 - win, 0 - lose;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    DP[1]=DP[3]=DP[4]=1;
    DP[2]=0;
    int n; cin>>n;
    for(int i = 5; i <= n; ++i)
        DP[i] = !(DP[i-1] && DP[i-3] && DP[i-4]);
    cout<<(DP[n]?"SK\n":"CY\n");
}