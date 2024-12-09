#include <iostream>
using namespace std;
int maxSumDP[500][500];
int R;
int triangle[500][500];
int maxSum(int r, int c){
    if(r>=R || c>r) return 0;
    if(maxSumDP[r][c]!=-1) return maxSumDP[r][c];
    return maxSumDP[r][c]=max(maxSum(r+1,c),maxSum(r+1,c+1))+triangle[r][c];
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int r=0; r<500; ++r)
        for(int c=0; c<500; ++c)
            maxSumDP[r][c]=-1;
    cin>>R;
    for(int r=0; r<R; ++r)
        for(int c=0; c<=r; ++c)
            cin>>triangle[r][c];
    cout<<maxSum(0,0)<<"\n";
}