#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Cow{
    int id, a, b;
    Cow(){}
    Cow(int i, int a, int b):id(i),a(a),b(b){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    vector<Cow> cows(n);
    for(int i = 0; i < n; ++i)
        cows[i].id=i;
    for(int i = 0; i < n; ++i)
        cin>>cows[i].a>>cows[i].b;
    sort(cows.begin(),cows.end(),[](const Cow &a, const Cow &b){
        return a.a>b.a;
    });
    vector<Cow> pre(cows.begin(),cows.begin()+k);
    sort(pre.begin(),pre.end(),[](const Cow &a, const Cow &b){
        return a.b>b.b;
    });
    cout<<pre[0].id+1<<"\n";
}