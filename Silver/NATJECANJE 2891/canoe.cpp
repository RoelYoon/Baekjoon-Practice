#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
struct Event{
    int s,e;
    Event(int s, int e):s(s),e(e){}
    Event(){} 
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,s,r; cin>>n>>s>>r;
    vector<int> S(s);
    for(int i = 0; i < s; ++i){
        cin>>S[i];
    }
    sort(S.begin(),S.end());
    int fix = 0;       
    vector<Event> R;
    vector<bool> f(s);
    for(int i = 0; i < r; ++i){
        int x; cin>>x;
        int lb = 0, rb = s-1;
        while(lb<rb){
            int mid = (lb+rb)/2;
            if(S[mid] < x){
                lb = mid+1;
            }else{
                rb = mid;
            }
        }
        if(S[lb]==x){
            f[lb] = 1;
            ++fix;
            continue;
        }
        R.emplace_back(x-1,x+1);
    }
    sort(R.begin(),R.end(),[](const Event &a, const Event &b){
        if(a.e == b.e) return a.s < b.s;
        return a.e<b.e; 
    });
    int j = 0;
    for(int i = 0; i < R.size(); ++i){
        while(j<s && (S[j]<R[i].s || f[j])){
            ++j;
        }
        if(S[j]<R[i].s || S[j]>R[i].e || f[j]) continue;
        f[j]=1;
        ++fix;
     }
    cout<<(s-fix<0?0:s-fix)<<"\n";
} 
