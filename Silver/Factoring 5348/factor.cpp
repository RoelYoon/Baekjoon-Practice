#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        bool p = 0;
        cout<<n<<": ";
        for(int x = 2; x*x<=n; ++x){
            int cnt = 0;
            while(n%x==0){
                cout<<x<<" ";
                n/=x;
                p = 1;
            }
        }
        if(!p){
            cout<<"prime\n";
            continue;
        }
        if(n>1){
            cout<<n;
        }
        cout<<"\n";
    }
}