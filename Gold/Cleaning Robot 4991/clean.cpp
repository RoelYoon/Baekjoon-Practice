#include <iostream>
#include <vector>
#include <queue>
#include <complex>
#include <algorithm>
#define ROW real()
#define COL imag()
#define INF ((int)1e9)
#define pt complex<int>
using namespace std;
const pt dir[4]{pt(0,1), pt(1,0), pt(0,-1), pt(-1,0)};
struct State{
    pt pos;
    int t;
    State(){}
    State(pt pos, int t):pos(pos),t(t){}
};
//string debug = "";
void travel(vector<vector<vector<int>>> &time, vector<pt> &pts, int visited, int &ans, int dist, int head){
    bool visitedAll = 1;
    for(int i = 0; i < pts.size(); ++i){
        if(!(visited&(1<<i))){
            //string add = "Traveling from ("+to_string(pts[head].ROW)+", "+to_string(pts[head].COL)+") to ("+to_string(pts[i].ROW)+", "+to_string(pts[i].COL)+")\n";
            //add+="Distance: "+to_string(time[head][pts[i].ROW][pts[i].COL])+"\n";
            //debug+=add;
            travel(time, pts, visited|(1<<i), ans, dist+time[head][pts[i].ROW][pts[i].COL], i);
            //for(int j = 0; j < add.size(); ++j)
                //debug.pop_back();
            visitedAll = 0;
        }
    }
    if(visitedAll){
        ans = min(ans, dist);
        //cout<<debug;
        //cout<<"Final dist: "<<dist<<"\n=============\n";
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    //freopen("output","w",stdout);
    while(1){
        int R,C; cin>>C>>R;
        if(!R && !C) break;
        vector<string> grid(R);
        vector<pt> dirty;
        pt robot;
        for(int r = 0; r < R; ++r){
            string s; cin>>s;
            grid[r]=s;
            for(int c = 0; c < C; ++c){
                if(grid[r][c]=='*'){
                    dirty.push_back(pt(r,c));
                }else if(grid[r][c]=='o'){
                    robot = pt(r,c);
                }
            }
        }
        dirty.push_back(robot);
        vector<vector<vector<int>>> time(dirty.size(), vector<vector<int>>(R, vector<int>(C, INF)));
        for(int j = 0; j < dirty.size(); ++j){
            queue<State> q;
            q.emplace(dirty[j], 0);
            time[j][dirty[j].ROW][dirty[j].COL] = 0;
            while(!q.empty()){
                State state = q.front(); q.pop();
                pt cur = state.pos;
                for(int i = 0; i < 4; ++i){
                    pt nxt = cur+dir[i];
                    if(nxt.ROW >= 0 && nxt.ROW < R && nxt.COL >= 0 && nxt.COL < C && state.t+1 < time[j][nxt.ROW][nxt.COL] && grid[nxt.ROW][nxt.COL]!='x'){
                        time[j][nxt.ROW][nxt.COL]=state.t+1;
                        q.emplace(nxt, state.t+1);
                    }
                }
            }
        }
        int ans = INF;
        travel(time, dirty, (1<<(dirty.size()-1)), ans, 0, dirty.size()-1);
        cout<<(ans>=INF || ans < 0?-1:ans)<<"\n";
    }
}
