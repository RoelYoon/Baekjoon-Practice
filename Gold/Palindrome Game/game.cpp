#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        string s; cin>>s;
        cout<<(s[s.size()-1]=='0'?"E":"B")<<"\n";
    }
}