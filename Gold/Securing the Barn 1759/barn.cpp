#include <iostream>
#include <algorithm>
using namespace std;
bool vowel[125]{};
char letters[100000];
int L,n;
void printAll(int v, int c, int d, int limit, string &s){
    if(d==L){
        if(v>0 && c>1)
            cout<<s<<"\n";
        return;
    }
    for(int i = 0; i < n; ++i){
        if(i>limit){
            s.push_back(letters[i]);
            printAll(v+vowel[letters[i]],c+!vowel[letters[i]],d+1,i,s);
            s.pop_back();
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>L>>n;
    for(int i = 0; i < n; ++i)
        cin>>letters[i];
    sort(letters,letters+n);
    vowel['a']=1,vowel['e']=1,vowel['i']=1,vowel['o']=1,vowel['u']=1;
    string s = "";
    printAll(0,0,0,-1,s);
}