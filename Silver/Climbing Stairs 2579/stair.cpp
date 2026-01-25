#include <iostream>
using namespace std;
int DP[301][2]{};
int score[301]{};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i=1; i <= n; ++i)
        cin>>score[i];
    DP[1][0]=score[1];
    DP[2][0]=score[2];
    DP[2][1]=score[1]+score[2];
    for(int i = 3; i <= n; ++i){
        DP[i][0] = max(DP[i-2][0],DP[i-2][1])+score[i];
        DP[i][1] = DP[i-1][0]+score[i];
    }
    cout<<max(DP[n][0],DP[n][1])<<"\n";
}