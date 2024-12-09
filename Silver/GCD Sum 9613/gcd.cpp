#include <iostream>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b);}
int lcm(int a, int b) { return a / gcd(a, b) * b; }
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        int nums[100];
        for(int i = 0; i < n; ++i)
            cin>>nums[i];
        long long sum = 0;
        for(int i = 0; i < n; ++i)
            for(int j = i+1; j < n; ++j)
                sum+=gcd(nums[i],nums[j]);
        cout<<sum<<"\n";
    }
}