#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> times(n);
    for(int i = 0; i < n; ++i)
        cin>>times[i];
    sort(times.begin(),times.end(),greater<int>());
    int maxReach = 0;
    for(int i = 0; i < n; ++i){
        maxReach=max(maxReach,max((times[i]+i)-(n-1),0));
    }
    cout<<maxReach+n+1<<"\n";
}