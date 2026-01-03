#include <iostream>
#define MAX 400000
using namespace std;
// 0-1 knapsack minimizing value
// condition change -> weights must >= capacity
int disk[100];
int DP[MAX+1];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; int e; cin>>n>>e;
        for(int i = 0; i < n; ++i)
            cin>>disk[i];
        if(e>MAX){
            cout<<"FULL\n";
            continue;
        }
        DP[0]=0;
        for(int i = 1; i <= e; ++i)
            DP[i]=MAX;
        for(int i = 0; i < n; ++i){
            for(int j = e; j>0; --j){
                int pi = max(0,j-disk[i]*2);
                DP[j] = min(DP[j], DP[pi]+disk[i]);
            }
        }
        cout<<(DP[e]==MAX?"FULL":to_string(DP[e]))<<"\n";
    }
}