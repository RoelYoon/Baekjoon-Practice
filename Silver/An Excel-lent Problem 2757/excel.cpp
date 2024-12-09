#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
string a = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    //freopen("test","r",stdin);
    while(1){
        string pos; cin>>pos;
        ll R = stoll(pos.substr(1,pos.find('C'))), C=stoll(pos.substr(pos.find('C')+1));
        if(R==0 && C==0) break;
        string cTxt="";
        while(C){
            C--;
            cTxt.push_back(a[C%26]);
            C/=26;
        }
        reverse(cTxt.begin(),cTxt.end());
        cout<<cTxt<<to_string(R)<<"\n";
    }
}