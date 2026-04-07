#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
class PS{
    int n;
    vector<ll> p;
    public:
    PS(int n, vector<int> &data):n(n),p(n){
        p[0] = data[0];
        for(int i = 1; i < n; ++i) {
            p[i] = p[i-1] + data[i];
        }
    }   
    ll sum(int L, int R){
        if(!L){
            return p[R];
        }
        return p[R]-p[L-1];
    }
};
ll diff(PS &ps, vector<int> &w, int t){
    int i = lower_bound(w.begin(), w.end(), t) - w.begin() - 1;
    int j = upper_bound(w.begin(), w.end(), t) - w.begin();
    ll L = 0, R = 0;
    if(i>=0){
        L = ps.sum(0, i);
    }
    if(j < w.size()){
        R = ps.sum(j, w.size()-1);
    }
    return L-R;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> w(n);
    for(int i = 0; i < n; ++i){
        cin>>w[i];
    }
    sort(w.begin(), w.end());
    PS ps(n,w);
    int lb = 0, rb = 200001;
    while(lb < rb){
        int mid = (lb+rb)/2;
        ll d = diff(ps, w, mid);
        // d < 0 --> t too low; d > 0 --> t too high
        if(d < 0){
            lb = mid+1;
        } else{
            rb = mid;
        }
    }
    cout<<lb<<"\n";
}
