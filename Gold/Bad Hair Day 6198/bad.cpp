#include <iostream>
#include <vector>
#include <cmath>
#define CHUNK(i) (i/s)
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> h(n);
    for(int i = 0; i < n; ++i)
        cin>>h[i];
    const int s = sqrt(n)+1;
    vector<int> hChunks(s);
    vector<int> sizes(s);
    for(int i = 0; i < n; ++i){
        hChunks[CHUNK(i)] = max(hChunks[CHUNK(i)],h[i]);
        ++sizes[CHUNK(i)];
    }
    ll ans = 0;
    for(int i = 0; i < n; ++i){
        ll cnt = 0;
        int c = CHUNK(i);
        bool stop = 0;
        for(int j = i+1; (CHUNK(j)==CHUNK(i)) && j<n; ++j){
            if(h[j] < h[i]){
                ++cnt;
            }else{
                stop = 1;
                break;
            }
        }
        ans+=cnt;
        if(stop) continue;
        cnt = 0;
        ++c;
        for(; c < s; ++c){
            if(hChunks[c] < h[i]){
                cnt+=sizes[c];
            }else{
                for(int j = c*s; j < min(n,((c+1)*s)); ++j){
                    if(h[j]<h[i]){
                        ++cnt;
                    }else{
                        break;
                    }
                }
                break;
            }
        }
        ans+=cnt;
    }
    cout<<ans<<"\n";
}