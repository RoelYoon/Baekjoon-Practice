#include <iostream>
using namespace std;
int turn(int a,int n, int d){
    return !(a%2)?(a+n)%d:((a-n)%d+d)%d;
}
int convert(int a, int kp, int n, int d){
    return a%2?((kp-n)%d+d)%d:(kp+n)%d;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    for(int i = 0; i < t; ++i){
        int k,d,n; cin>>d>>k>>n;
        --k;
        int kp = turn(k,n,d);
        cout<<"Case #"<<i+1<<": "<<convert(k,(kp+1)%d,n,d)+1<<" "<<convert(k,((kp-1)%d+d)%d, n, d)+1<<"\n";
    }
}