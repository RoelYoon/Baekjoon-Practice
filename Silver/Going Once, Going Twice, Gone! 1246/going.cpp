#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin>>n>>m;
    vector<int> p(m);
    for(int i = 0; i < m; ++i)
        cin>>p[i];
    sort(p.begin(),p.end(),greater<int>());
    int mx = 0;
    int pc = 0;
    for(int i = 0; i < m; ++i){
        int x = (i-max(-1,i-n))*p[i];
        if(x>mx){
            mx=x;
            pc=p[i];
        }
    }
    cout<<pc<<" "<<mx<<"\n";
}