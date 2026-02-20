#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    int n[15];
    while(T--){
        int t; cin>>t;
        for(int i = 0; i < 15; ++i){
            cin>>n[i];
        }
        int cnt = 0;
        for(int i = 1; i < 15; ++i){
            int c = n[i-1];
            bool reachedEnd = 0;
            bool increase = 0;
            for(int j = i; j < 15; ++j){
                if(n[j]<=c){
                    reachedEnd = j!=i;
                    break;
                }
                if(n[j]>c){
                    increase=1;
                }
            }
            cnt+=reachedEnd && increase;
        }
        cout<<t<<" "<<cnt<<"\n";
    }
}
