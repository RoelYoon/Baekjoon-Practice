#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
struct Task{
    ll d,t;
    Task(){}
    Task(ll d, ll t):d(d),t(t){};
    bool operator<(const Task &k) const {
        return t>k.t;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Task> tasks(n);
    for(int i = 0; i < n; ++i)
        cin>>tasks[i].d>>tasks[i].t;
    sort(tasks.begin(),tasks.end());
    ll time = tasks[0].t;
    for(int i = 0; i < n-1;++i){
        time=min(time-tasks[i].d,tasks[i+1].t);
    }
    time-=tasks.back().d;
    cout<<time<<"\n";
}
/*
2
3 5
3 6
ANS: 0
*/