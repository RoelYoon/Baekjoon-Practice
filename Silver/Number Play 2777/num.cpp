#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        if(n==1){
            cout<<"1\n";continue;
        }
        string num="";
        for(int i = 9; i >= 2; --i){
            while(!(n%i)){
                n/=i;
                num+=to_string(i);
            }
        }
        cout<<(n!=1?(int)-1:(int)num.size())<<"\n";
    }
}