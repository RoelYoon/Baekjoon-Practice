#include <iostream>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    string zTime,zUTCs;
    cin>>zTime>>zUTCs;
    int UTC = stoi(zTime.substr(0,2))*60+stoi(zTime.substr(3,2))+(zUTCs[3]=='-'?round(stold(zUTCs.substr(4))*60):-round(stold(zUTCs.substr(4))*60));
    for(int i = 0; i < n; ++i){
        string UTCs; cin>>UTCs;
        int time = UTC+(UTCs[3]=='+'?round(stold(UTCs.substr(4))*60):-round(stold(UTCs.substr(4))*60));
        time=(time+1440)%1440;
        cout<<(!((time/60)/10)?"0":"")<<time/60<<":"<<((!((time%60)/10)?"0":""))<<time%60<<"\n";
        //cout<<time<<"\n";
    }    
}
/*
4
00:00 UTC+0
UTC+9.5
UTC-1
UTC+12
UTC+10
*/