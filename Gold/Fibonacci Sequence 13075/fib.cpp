#include <iostream>
#define ll long long
#define MOD ((ll)1e9)
using namespace std;
void multiplyMat(ll a[2][2], ll b[2][2], ll ans[2][2]){
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            for(int k = 0; k < 2; ++k){
                ans[i][j]+=(a[i][k]*b[k][j])%MOD;
                ans[i][j]%=MOD;
            }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    ll exp[50][2][2]{};
    exp[1][0][0]=exp[1][1][0]=exp[1][0][1]=1;
    for(int i = 1; i <= 49; ++i)
        multiplyMat(exp[i-1],exp[i-1],exp[i]);
    while(t--){
        ll n; cin>>n;
        ll ans[2][2]{{1,0},{0,1}};
        for(int i = 0; i <= 48; ++i){
            if(n&(1L<<i)){
                ll temp[2][2]{};
                multiplyMat(ans,exp[i+1],temp);
                for(int r = 0; r < 2; ++r)
                    for(int c = 0; c < 2; ++c)
                        ans[r][c]=temp[r][c];
            }
        }
        cout<<ans[0][1]<<"\n";
    }
}