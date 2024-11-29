#include <iostream>
#include <vector>
using namespace std;
struct KMP{
    int m;
    string P;
    vector<int> reset;
    KMP(int m):m(m),reset(m+1){
        getline(cin,P);
        int i=0,j=-1; reset[i]=j;
        while(i<m){
            while(j>=0 && P[i]!=P[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n; cin.ignore();
    KMP kmp(n);
    cout<<n-kmp.reset.back()<<"\n";
}