#include <iostream>
#include <vector>
using namespace std;
struct Player{
    int w;
    int b;
    Player(){}
    Player(int w, int b):w(w),b(b){}
};
int n=0;
int maxScore = 0;
vector<vector<vector<int>>> mem;
vector<Player> players;
void findMax(int score, int b, int w, int i){
    if(w==15 && b==15){
        maxScore=max(maxScore,score);
        return;
    }
    if(i>=n || mem[b][w][i]>=score){return;}
    mem[b][w][i]=score;
    //pick black
    if(b<15){
        findMax(score+players[i].b,b+1,w,i+1);
    }
    //pick white
    if(w<15){
        findMax(score+players[i].w,b,w+1,i+1);
    }
    //pick no one
    findMax(score,b,w,i+1);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int w, b;
    while(cin>>w>>b){
        players.emplace_back(w,b);
        ++n;
    }
    mem=vector<vector<vector<int>>>(16,vector<vector<int>>(16,vector<int>(n,-1)));
    findMax(0,0,0,0);
    cout<<maxScore<<"\n";
}