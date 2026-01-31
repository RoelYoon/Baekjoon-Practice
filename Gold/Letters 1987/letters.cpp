#include <iostream>
#include <vector>
using namespace std;
int R,C;
int ans = 0;
vector<string> grid;
const int dirR[4]{0,1,0,-1};
const int dirC[4]{1,0,-1,0};
void DFS(int s, int r, int c, int d){
    ans = max(ans,d);
    for(int i = 0; i < 4; ++i){
        int nr = r+dirR[i];
        int nc = c+dirC[i];
        if(nr>=0 && nr<R && nc>=0 && nc<C && !((1<<(grid[nr][nc]-'A'))&s))
            DFS((1<<(grid[nr][nc]-'A'))|s, nr, nc, d+1);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C;
    grid.resize(R);
    for(int r = 0; r < R; ++r)
        cin>>grid[r];
    DFS((1<<(grid[0][0]-'A')),0,0,1);
    cout<<ans<<"\n";
}