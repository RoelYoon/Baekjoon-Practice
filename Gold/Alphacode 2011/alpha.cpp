#include <iostream>
#define ll long long
#define M 1000000
using namespace std;
ll DP[5005]{};
string s;
ll countWays(int p){
    if(p>=s.size()) return 1;
    if(DP[p]) return DP[p];
    ll ways=0;
    if(s[p]!='0')
        ways=countWays(p+1)%M;
    if(ways<0) return ways;
    if(p<s.size()-1){
        string ss = s.substr(p,2);
        if(ss=="00") return -1e18;
        if(ss[0]!='0' && stoi(ss)<27){
            ways+=countWays(p+2)%M;
            if(ways<0) return ways;
        }
    }
    return DP[p]=ways%M;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>s;
    cout<<(s[0]=='0'?0:countWays(0)<0?0:DP[0])<<"\n";
}