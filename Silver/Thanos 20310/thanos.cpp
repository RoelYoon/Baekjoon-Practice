#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; cin>>s;
    int oCnt=0,lCnt=0;
    for(int i = 0; i < s.size(); ++i){
        oCnt+=s[i]=='0';
        lCnt+=s[i]=='1';
    }
    oCnt/=2,lCnt/=2;
    int oCnt2=0,lCnt2=0;
    string ans="";
    for(int i = 0; i < s.size(); ++i){
        if(s[i]=='0' && oCnt2<oCnt){
            ans.push_back(s[i]);
        }else if(s[i]=='1' && lCnt2>=lCnt){
            ans.push_back(s[i]);
        }
        oCnt2+=s[i]=='0';
        lCnt2+=s[i]=='1';
    }
    cout<<ans<<"\n";
}