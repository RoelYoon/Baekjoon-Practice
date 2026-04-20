#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; cin>>s;
    bool hiss = 0;
    for(int i = 0; i < s.size()-1; ++i){
        if(s[i]=='s' && s[i+1]=='s'){
            hiss = 1;
            break;
        }
    }
    if(hiss){
        cout<<"hiss\n";
    }else{
        cout<<"no hiss\n";
    }
}