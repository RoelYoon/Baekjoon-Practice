#include <iostream>
#include <map>
using namespace std;
map<short,int> freq;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    for(int i = 0; i < n; ++i){
        short x; cin>>x;
        map<short,int>::iterator it = freq.find(x);
        if(it!=freq.end()){
            it->second++;
        }else{
            freq.insert({x,1});
        }
    }
    for(map<short,int>::iterator it = freq.begin(); it!=freq.end(); ++it)
        for(int i = 0; i < it->second; ++i)
            cout<<it->first<<"\n";
}