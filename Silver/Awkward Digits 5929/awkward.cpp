#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int bVal(string &b){
    int db=0;
    for(int p = 0; p < b.size(); ++p)
        db+=pow(2,p)*(b[b.size()-1-p]-48);
    return db;
}
int tVal(string &t){
    int dt=0;
    for(int p = 0; p < t.size(); ++p)
        dt+=pow(3,p)*(t[t.size()-1-p]-48);
    return dt;
}
bool equal(string &b, string &t){
    return bVal(b)==tVal(t);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string b,t; cin>>b>>t;
    for(int i = 0; i < b.size(); ++i){
        for(int j = 0; j < 2; ++j){
            b[i]=(b[i]-48+1)%2+48;
            for(int ii = 0; ii < t.size(); ++ii){
                for(int jj = 0; jj < 3; ++jj){
                    t[ii]=(t[ii]-48+1)%3+48;
                    if(equal(b,t)){
                        cout<<bVal(b)<<"\n";
                        return 0;
                    }
                }
            }
        }
    }
}