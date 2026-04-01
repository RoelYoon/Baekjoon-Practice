#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
struct Event{
    ll x;
    bool e;
    Event(){}
    Event(ll x, bool e):x(x),e(e){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; ll s; cin>>n>>s;
    vector<Event> events;
    for(int i = 0; i < n; ++i){
        int L,R;
        cin>>L>>R;
        events.emplace_back(L,0);
        events.emplace_back(R,1);
    }
    sort(events.begin(), events.end(), [](const Event &a, const Event &b){
        return a.x < b.x;
    });
    ll x = 0;
    ll cnt = 0;
    for(int i = 0; i < events.size(); ++i){
        if(events[i].x <= x) continue;
        if(events[i].e){
            ll m = (events[i].x - x)/s + ((events[i].x - x)%s > 0);
            x+=m*s;
            cnt+=m;
        }else{
            ++cnt;
            x = events[i].x+s;
        }
    }
    cout<<cnt<<"\n";
}