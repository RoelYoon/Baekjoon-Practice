#include <iostream>
using namespace std;
bool generated[100000]{};
int d(int n){
    int result = n;
    while(n){
        result+=n%10;
        n/=10;
    }
    return result;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 1; i < 10000; ++i){
        generated[d(i)]=1;
        if(!generated[i])
            cout<<i<<"\n";
    }
}