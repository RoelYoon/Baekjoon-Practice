#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;
unordered_set<string> d;
string longest="";
string alphabet="abcdefghijklmnopqrstuvwxyz";
unordered_set<string> v;
void makeLongest(string &s){
    if(d.find(s)==d.end() || v.find(s)!=v.end()) return;
    v.insert(s);
    if(longest.size()<s.size()){
        longest=s;
    }
    for(int i = 0; i <= s.size(); ++i){
        for(int j = 0; j < 26; ++j){
            s=s.substr(0,i)+alphabet[j]+s.substr(i);
            makeLongest(s);
            s=s.substr(0,i)+s.substr(i+1);
        }
    }
    if(longest.size()<s.size()){
        longest=s;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    string s; cin>>s;
    for(int i = 0; i < n; ++i){
        string t; cin>>t;
        d.insert(t);
    }
    makeLongest(s);
    cout<<longest<<"\n";
}
