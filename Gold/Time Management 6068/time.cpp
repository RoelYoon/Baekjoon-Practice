#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Task{
    int d,t;
    Task(){}
    Task(int d, int t):d(d),t(t){};
    bool operator<(const Task &k) const {
        return d>k.d;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Task> tasks(n);
    for(int i = 0; i < n; ++i)
        cin>>tasks[i].t>>tasks[i].d;
    sort(tasks.begin(),tasks.end());
    int time = 1e9;
    for(int i = 0; i < n-1;++i){
        time=min(time-tasks[i].t,tasks[i+1].d);
    }
    time-=tasks.back().t;
    cout<<(time<0?-1:time)<<"\n";
}