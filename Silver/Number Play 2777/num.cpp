#include <iostream>
using namespace std;
int main(){
    int t;cin>>t;
    while(t--){
        int n,c=0;cin>>n;
        if(n==1){cout<<"1\n";continue;}
        for(int i=9;i>=2;--i)
            while(!(n%i)){
                n/=i;
                ++c;
            }
        cout<<(n!=1?(int)-1:c)<<"\n";
    }
}