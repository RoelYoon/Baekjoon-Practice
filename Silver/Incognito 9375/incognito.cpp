#include <iostream>
#include <unordered_map>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        unordered_map<string,int> map;
        int n; cin>>n;
        for(int i = 0; i < n; ++i){
            string item,type;
            cin>>item>>type;
            map[type]++;
        }
        int num = 1;
        for(unordered_map<string,int>::iterator it=map.begin(); it!=map.end(); ++it){
            num*=(it->second+1);
        }
        cout<<num-1<<"\n";
    }
}