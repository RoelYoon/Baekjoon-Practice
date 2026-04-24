#include <iostream>
using namespace std;
const int M = 9973;
int modPow(int a, int b){
    int res = ((45*25 + 45*75)%M + 25*45)%M;
    while(b){
        if(b&1){
            res = (res*a)%M;
        }
        a = (a*a)%M;
        b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        n-=4;
        cout<<modPow(10,n)<<"\n";    
    }   
}