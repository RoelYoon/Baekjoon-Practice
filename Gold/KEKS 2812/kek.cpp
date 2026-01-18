#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
struct Pair{
    char v;
    int i;
    Pair(){}
    Pair(char v, int i):v(v),i(i){}
    struct CMP{
        bool operator()(const Pair &a, const Pair &b) const {
            if(a.v==b.v) return a.i<b.i;
            return a.v<b.v;
        }
    };
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    string s; cin>>s;
    reverse(s.begin(),s.end());
    int e = s.size();
    string ans = "";
    priority_queue<Pair,vector<Pair>,Pair::CMP> pq;
    int pqI = e;
    while(e>0){
        while(!pq.empty() && pq.top().i >= e){
            pq.pop();
        }
        while(pqI>0 && pqI != e-1-k){
            pq.emplace(s[--pqI],pqI);
        }
        if(pq.empty()) break;
        ans.push_back(pq.top().v);
        k-=(e-pq.top().i)-1;
        e-=(e-pq.top().i);
        
    }
    while(k--)
        ans.pop_back();
    cout<<ans<<endl;
}