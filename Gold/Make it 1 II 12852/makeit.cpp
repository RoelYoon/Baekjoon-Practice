#include <iostream>
#define MAX_N 1000001
#define INF 1000000000
using namespace std;
void traceback(int trace[], int n){
    if(n==1){
        cout<<"1\n";
        return;
    }
    cout<<n<<" ";
    traceback(trace, trace[n]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    int trace[MAX_N];
    int DP[MAX_N];
    for(int i = 0; i <= n; ++i){
        DP[i] = INF;
        trace[i] = -1;
    }
    DP[1] = 0;
    trace[1] = 1;
    for(int i = 1; i <= n; ++i){
        if(i+1 < MAX_N){
            if(DP[i]+1 < DP[i+1]){
                DP[i+1] = DP[i]+1;
                trace[i+1] = i;
            }
        }
        if(i*2 < MAX_N){
            if(DP[i]+1 < DP[i*2]){
                DP[i*2] = DP[i]+1;
                trace[i*2] = i;
            }
        }
        if(i*3 < MAX_N){
            if(DP[i]+1 < DP[i*3]){
                DP[i*3] = DP[i]+1;
                trace[i*3] = i;
            }
        }
    }
    cout<<DP[n]<<"\n";
    traceback(trace, n);
}