#include <iostream>
#define MAX 40
#define ll long long
using namespace std;
struct Pair{
    ll a,b;
    Pair(){}
    Pair(ll a, ll b):a(a),b(b){}
    Pair operator+(const Pair &k) const {
        return Pair(a+k.a,b+k.b);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    Pair DP[MAX+1];
    DP[0]=Pair(1,0);
    DP[1]=Pair(0,1);
    for(int i = 2; i <= 40; ++i){
        DP[i]=DP[i-1]+DP[i-2];
    }
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        cout<<DP[n].a<<" "<<DP[n].b<<"\n";
    }
}