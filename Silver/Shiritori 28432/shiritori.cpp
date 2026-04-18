#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<string> wordList;
    unordered_set<string> wordSet;
    int mI = 0;
    for(int i = 0; i < n; ++i){
        string s; cin>>s;
        if(s=="?"){
            mI = i;
            continue;
        }
        wordList.push_back(s);
        wordSet.insert(s);
    }
    int m; cin>>m;
    char l='*',f='*';
    if(mI != 0){
        l = wordList[mI-1].back();
    }
    if(mI != n-1){
        f = wordList[mI].front();
    }
    vector<string> ans;
    for(int i = 0; i < m; ++i){
        string s; cin>>s;
       if((wordSet.find(s) != wordSet.end()) || !((s[0] == l || l == '*') && (s.back() == f || f == '*'))){
            continue;
       }
        ans.push_back(s);
    }
    for(int i = 0;  i < ans.size(); ++i){
        cout<<ans[i]<<"\n";
    }
}