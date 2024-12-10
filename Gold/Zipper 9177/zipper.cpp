#include <iostream>
using namespace std;
string s1,s2,s;
bool match(string &cur){
    for(int i = 0; i < cur.size(); ++i)
        if(cur[i]!=s[i])
            return 0;
    return 1;
}
bool visited[205][205]{};
bool found;
void find(string &cur, int a, int b){
    if(visited[a][b] || found || cur.size()>s.size() || !match(cur)) return;
    visited[a][b]=1;
    if(cur.size()==s.size()){
        cout<<"yes\n";
        found=1;
        return;
    }
    cur.push_back(s1[a]);
    find(cur,a+1,b);
    cur.pop_back();
    cur.push_back(s2[b]);
    find(cur,a,b+1);
    cur.pop_back();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    for(int t = 0; t < T; ++t){
        found=0;
        for(int i = 0; i < 205; ++i)
            for(int j = 0; j < 205; ++j)
                visited[i][j]=0;
        cin>>s1>>s2>>s;
        cout<<"Data set "<<t+1<<": ";
        string cur = "";
        find(cur,0,0);
        if(!found)
            cout<<"no\n";
    }
}