#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
ll n,m,L;
ll cnt = 0;
vector<ll>::iterator closestHunter(vector<ll> &hunters, ll x){
    vector<ll>::iterator i = lower_bound(hunters.begin(),hunters.end(),x);
    vector<ll>::iterator j = i-1;
    return i==hunters.begin()?i:(abs(*i-x) < abs(*j-x))?i:j;
}
ll distance(ll hunterX, ll x, ll y){
    return abs(hunterX-x)+y;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>m>>n>>L;
    vector<ll> hunters(m);
    for(int i = 0; i < m; i++)
        cin>>hunters[i];
    sort(hunters.begin(),hunters.end());
    for(int i = 0; i < n; i++){
        ll x,y; cin>>x>>y; 
        ll hunterX = *closestHunter(hunters,x);
        cnt+=distance(hunterX,x,y)<=L;
    }
    cout<<cnt<<"\n";
}  
