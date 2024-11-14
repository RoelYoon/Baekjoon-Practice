#include <iostream>
#include <string>
using namespace std;
int n;
int findNum(string &s, int &k){
    string num = "";
    while(k < s.size() && s[k]!='+' && s[k]!='-'){
        if(s[k]!=' ')
            num+=s[k];
        ++k;
    }
    return stoi(num);
}
void find(int i, string &s){
    if(i==n) {
        int k = 0;
        int sum = findNum(s,k);
        for(; k < s.size();)
            s[k++]=='+'?sum+=findNum(s,k):sum-=findNum(s,k);
        if(!sum)
            cout<<s<<"\n";
        return;
    }
    s+=" "+to_string(i+1);
    find(i+1,s);
    s.pop_back();
    s.pop_back();
    s+="+"+to_string(i+1);
    find(i+1,s);
    s.pop_back();
    s.pop_back();
    s+="-"+to_string(i+1);
    find(i+1,s);
    s.pop_back();
    s.pop_back();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        cin>>n;
        string s = "1";
        find(1,s);
        cout<<"\n";
    }
}