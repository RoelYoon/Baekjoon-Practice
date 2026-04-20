#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    unordered_map<string, int> scores;
    vector<string> winners;
    int n,p,m; cin>>n>>p>>m;
    for(int i = 0; i < n; ++i){
        string name ; cin>>name;
        scores.insert({name,0});
    }
    for(int i = 0; i < m; ++i){
        string name; int c; cin>>name>>c;
        if(scores[name]==-1) continue;
        scores[name]+=c;
        if(scores[name]>=p){
            winners.push_back(name);
            scores[name] = -1;
        }
    }
    if(winners.empty()){
        cout<<"No winner!\n";
    }
    for(int i = 0; i < winners.size(); ++i){
        cout<<winners[i]<<" wins!\n";
    }
}