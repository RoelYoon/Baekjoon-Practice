#include <iostream>
#define ll long long
using namespace std;
ll DP[1024][1024];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n>>m;
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            cin>>DP[r][c];
            if(r!=0){
                DP[r][c]+=DP[r-1][c];
            }
            if(c!=0){
                DP[r][c]+=DP[r][c-1];
            }
            if(r!=0 && c!=0){
                DP[r][c]-=DP[r-1][c-1];
            }
        }
    }
    for(int i = 0; i < m; ++i){
        int a,b,c,d; cin>>a>>b>>c>>d;
        --a,--b,--c,--d;
        ll ans = DP[c][d];
        if(a!=0){
            ans-=DP[a-1][d];
        }
        if(b!=0){
            ans-=DP[c][b-1];
        }
        if(a!=0 && b!=0){
            ans+=DP[a-1][b-1];
        }
        cout<<ans<<"\n";
    }
}