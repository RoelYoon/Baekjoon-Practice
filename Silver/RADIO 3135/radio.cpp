#include <iostream>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a,b,n; cin>>a>>b>>n;
    vector<int> f(n);
    for(int i = 0; i < n; ++i)
        cin>>f[i];
    int minDist = abs(b-a);
    for(int i = 0; i < n; ++i)
        if(abs(b-f[i])+1<minDist)
            minDist=abs(b-f[i])+1;
    cout<<minDist<<"\n";
}