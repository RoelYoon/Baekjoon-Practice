#include <iostream>
#include <vector>
#define ll long long
using namespace std;
struct Candy{
    ll cost, cal;
    Candy(){}
    Candy(ll cost, ll cal):cost(cost),cal(cal){}
};
Candy candies[5001];
ll DP[10001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        int n,m; long double fm; cin>>n>>fm;
        m = (fm*100+0.5);
        if(n==0 && m==0) break;
        for(int i = 1; i <= n; ++i){
            ll cost,calorie; cin>>calorie>>fm;
            cost = (fm*100+0.5);
            candies[i]=Candy(cost,calorie);
        }
        for(int i = 0; i <= m; ++i){
            DP[i]=0;
        }
        for(int i = 1; i <= n; ++i){
            for(int j = candies[i].cost; j <= m; ++j){
                DP[j]=max(DP[j],DP[j-candies[i].cost]+candies[i].cal);
            }
        }
        cout<<DP[m]<<"\n";
    }
}