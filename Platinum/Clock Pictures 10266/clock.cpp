#include <iostream>
#include <bitset>
#include <vector>
#define DEG 360000
using namespace std;
class KMP{
    int m;
    bitset<DEG> P;
    vector<int> reset;
    public:
    KMP(int n):m(DEG),P(0),reset(m+1){
        for(int i = 0; i < n; ++i){
            int t; cin>>t;
            P[t]=1;
        }
        int i=0,j=-1; reset[i]=j;
        while(i<m){
            while(j>=0 && P[i]!=P[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
    }
    bool search(bitset<DEG*2> &T){
        int i=0,j=0;
        while(i<T.size()){
            while(j>=0 && T[i]!=P[j])
                j=reset[j];
            ++i,++j;
            if(j==m)
                return 1;
        }
        return 0;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    bitset<DEG*2> T(0);
    for(int i = 0; i < n; ++i){
        int t; cin>>t;
        T[t]=1;
        T[t+DEG]=1;
    }
    KMP kmp(n);
    cout<<(kmp.search(T)?"possible\n":"impossible\n");
}