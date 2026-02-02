#include <iostream>
#include <vector>
#include <queue>
#define INF ((int)1e9)
using namespace std;
struct Pos{
    int r,c,t;
    Pos(){}
    Pos(int r, int c, int t):r(r),c(c),t(t){}
};
const int dirR[4]{0,1,0,-1};
const int dirC[4]{1,0,-1,0};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int R,C; cin>>C>>R;
        vector<string> grid(R);
        Pos start;
        queue<Pos> q;
        vector<vector<int>> time(R,vector<int>(C,INF));
        for(int r = 0; r <R ; ++r){
            string s; cin>>s;
            for(int c = 0; c< C; ++c){
                grid[r]=s;
                if(grid[r][c]=='@'){
                    start = Pos(r,c,0);
                }
                else if(grid[r][c]=='*'){
                    q.emplace(r,c,0);
                    time[r][c]=0;
                }
            }
        }
        while(!q.empty()){
            Pos cur = q.front(); q.pop();
            for(int i = 0; i < 4; ++i){
                int nr = cur.r + dirR[i];
                int nc = cur.c + dirC[i];
                if(nr>=0 && nr<R && nc>=0 && nc<C && time[nr][nc]>cur.t+1 && grid[nr][nc]!='#'){
                    q.emplace(nr,nc,cur.t+1);
                    time[nr][nc]=cur.t+1;
                }
            }
        }
        vector<vector<int>> pTime(R,vector<int>(C,INF));
        q.push(start);
        bool possible = 0;
        int ans = -1;
        while(!q.empty()){
            Pos cur = q.front(); q.pop();
            if(cur.r==0 ||  cur.c==0 || cur.r==R-1 || cur.c == C-1){
                possible=1;
                ans = cur.t+1;
                break;
            }
            for(int i = 0; i < 4; ++i){
                int nr = cur.r + dirR[i];
                int nc = cur.c + dirC[i];
                if(nr>=0 && nr<R && nc>=0 && nc<C && time[nr][nc]>cur.t+1 && pTime[nr][nc]>cur.t+1 && grid[nr][nc]!='#'){
                    q.emplace(nr,nc,cur.t+1);
                    pTime[nr][nc]=cur.t+1;
                }
            }
        }
        if(possible){
            cout<<ans<<"\n";
        }else{
            cout<<"IMPOSSIBLE\n";
        }
    }

}
