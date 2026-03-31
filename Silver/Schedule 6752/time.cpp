#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    int n; cin>>n;
    vector<int> chores(n);
    for(int i = 0; i < n; ++i)
        cin>>chores[i];
    sort(chores.begin(), chores.end());
    int t = 0,cnt = 0;
    for(int i = 0; i < n; ++i){
        t+=chores[i];
        if(t<=T){
            ++cnt;
        }
        if(t>=T){
            break;
        }
    }
    cout<<cnt<<"\n";
}