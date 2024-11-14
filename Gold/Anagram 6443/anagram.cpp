#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
using namespace std;
void generate(unordered_set<string> &set,vector<bool> &included, string &s, string &cur){
    if(set.find(cur)!=set.end()) return;
    set.insert(cur);
    if(cur.size()==s.size()){
        cout<<cur<<"\n";
        return;
    }
    for(int i = 0; i < s.size(); ++i){
        if(!included[i]){
            included[i]=1;
            cur+=s[i];
            generate(set,included,s,cur);
            cur.pop_back();
            included[i]=0;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        string s,cur=""; cin>>s;
        sort(s.begin(),s.end());
        vector<string> ans;
        vector<bool> included(s.size());
        unordered_set<string> set;
        generate(set,included,s,cur);
    }
}