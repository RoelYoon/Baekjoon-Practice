#include <iostream>
using namespace std;
bool DP[5001][100]{};
int minCnt = 1e9;
void minP(int n, int cnt){
    if(n==0){
        minCnt=min(minCnt,cnt);
        return;
    }
    if(n<0 || DP[n][cnt]) return;
    DP[n][cnt]=1;
    minP(n-5,cnt+1);
    minP(n-3,cnt+1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    minP(n,0);
    cout<<(minCnt==1e9?-1:minCnt)<<"\n";
}