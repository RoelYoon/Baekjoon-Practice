#include <iostream>
#include <vector>
#include <queue>
#define INF ((int) 1e9)
using namespace std;
const int dirR[4]{0,1,0,-1};
const int dirC[4]{1,0,-1,0};
struct State{
    int r,c,t;
    bool g;
    State(){}
    State(int r, int c, int t):r(r),c(c),t(t),g(0){}  
    State(int r, int c, int t, bool g):r(r),c(c),t(t),g(g){}  
    bool operator==(const State &k) const {
        return r==k.r && c==k.c; 
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R,C,T; cin>>R>>C>>T;
    vector<vector<int>> grid(R,vector<int>(C));
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            cin>>grid[r][c];
        }
    }
    queue<State> q;
    q.emplace(0,0,0);
    vector<vector<int>> time(R,vector<int>(C,INF));
    vector<vector<bool>> gHad(R,vector<bool>(C,0));
    time[0][0] = 0;
    State P(R-1,C-1,0);
    int t = -1;
    while(!q.empty()){
        State cur = q.front(); q.pop();
        if(cur == P){
            t = cur.t;
            break;
        }
        if(grid[cur.r][cur.c]==2){
            cur.g = 1;
        }
        for(int i = 0; i < 4; ++i){
            int nxtR = cur.r + dirR[i];
            int nxtC = cur.c + dirC[i];
            if(nxtR>=0 && nxtR<R && nxtC>=0 && nxtC<C && (time[nxtR][nxtC]>cur.t+1 || (gHad[nxtR][nxtC]==0 && cur.g)) && (cur.g || grid[nxtR][nxtC]!=1)){
                q.emplace(nxtR,nxtC,cur.t+1,cur.g);       
                gHad[nxtR][nxtC]=cur.g;
                time[nxtR][nxtC]=cur.t+1;
            } 
        }
    }
    if(t==-1 || t>T){
        cout<<"Fail\n";
    }else{
        cout<<t<<"\n";
    }
}
