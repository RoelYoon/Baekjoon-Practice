#include <iostream>
#define ll long long
using namespace std;
const ll M = ((ll)1e9+7);
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    if(!n){
        cout<<"0\n";
        return 0;
    }
    ll a=1,b=1,c=b;
    for(int i = 3; i <= n; ++i){
        c = (a+b)%M;
        a = b;
        b = c;
    }
    cout<<c<<"\n";
}