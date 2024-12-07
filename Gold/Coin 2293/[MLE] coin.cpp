#include <iostream>
using namespace std;
int cnt[100][10001]{};
int coin[100];
int count(int i, int k){
    if(!k) return 1;
    if(i<0 || k<0) return 0;
    if(cnt[i][k]!=-1) return cnt[i][k];
    return cnt[i][k]=count(i-1,k)+count(i,k-coin[i]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 0; i < 100; ++i)
        for(int j = 0; j < 10001; ++j)
            cnt[i][j]=-1;
    int n,k; cin>>n>>k;
    for(int i = 0; i < n; ++i)
        cin>>coin[i];
    cout<<count(n-1,k)<<"\n";
}