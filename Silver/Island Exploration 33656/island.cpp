#include <iostream>
#include <vector>
#include <complex>
#include <string>
#define pt complex<int>
#define ROW real()
#define COL imag()
using namespace std;
const pt dir[4]{pt(0,1),pt(1,0),pt(0,-1),pt(-1,0)};
int R,C;
void DFS(vector<string> &map, vector<vector<bool>> &visited, pt cur) {
    if(visited[cur.ROW][cur.COL])
        return;
    visited[cur.ROW][cur.COL] = 1;
    for(int i = 0; i < 4; ++i){
        pt nxt = cur+dir[i];
        if(nxt.ROW>=0 && nxt.ROW<R && nxt.COL>=0 && nxt.COL<C && map[nxt.ROW][nxt.COL]=='#'){
            DFS(map, visited, nxt);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C;
    vector<string> map(R);
    pt start;
    for(int r = 0; r < R; ++r){
        cin>>map[r];
        for(int c = 0; c < C; ++c){
            if(map[r][c] == 'S'){
                start = pt(r,c);
            }
        }
    }
    int ans = 0;
    vector<vector<bool>> visited(R,vector<bool>(C));
    DFS(map,visited,start);
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            ans+=visited[r][c];
        }
    }
    cout<<ans<<"\n";
}