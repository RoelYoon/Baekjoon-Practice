#include <iostream>
#include <vector>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        vector<int> s(n);
        vector<int> m(n);
        for(int i = 0; i < n; ++i)
            cin>>s[i];
        int mx = s.back();
        m[n-1]=mx;
        for(int i = n-2; i >= 0; --i)
            m[i]=max(s[i],m[i+1]);
        ll mxP = 0;
        for(int i = 0; i < n; ++i){
            if(m[i]>s[i]){
                mxP+=m[i]-s[i];
            }
        }
        cout<<mxP<<"\n";
    }
}