#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Pair{
    int n;
    int i;
    Pair(){}
    Pair(int n, int i):n(n),i(i){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    vector<Pair> ns(T);
    int ans1[50],ans2[50];
    for(int t = 0; t < T; ++t){
        cin>>ns[t].n;
        ns[t].i = t;
    }
    sort(ns.begin(), ns.end(), [](const Pair &a, const Pair &b){
        return a.n < b.n;
    });
    int cnt = 0;
    int cntAll = 0;
    bool found[100001]{};
    int j = 0;
    for(int i = 2; i <= ns.back().n; ++i){
        int n = i;
        for(int x = 2; x*x <= n; ++x){
            int p = 0;
            while(n%x == 0){
                n/=x;
                ++p;
            }
            if(p){
                if(!found[x]){
                    found[x]=1;
                    ++cnt;
                }
                cntAll+=p;
            }
        }
        if(n > 1){
            if(!found[n]){
                found[n]=1;
                ++cnt;
            }
            cntAll+=1;
        } 
        while(i==ns[j].n){
            ans1[ns[j].i] = cnt;
            ans2[ns[j].i] = cntAll;
            ++j;
        }
    }
    for(int t = 0; t < T; ++t){
        cout<<ans1[t]<<" "<<ans2[t]<<"\n";
    }
}