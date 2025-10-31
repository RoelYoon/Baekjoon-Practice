#include <iostream>
#include <vector>
#include <complex>
#include <queue>
#define pt complex<int>
#define X real()
#define Y imag()
using namespace std;
const int dirR[4]{0,1,0,-1}, dirC[4]{1,0,-1,0};
int R,C;
inline int dot(pt a, pt b){
    return a.X*b.X + a.Y*b.Y;
}
inline bool inBounds(pt p){
    return p.X >= 0 && p.X < C && p.Y>= 0 && p.Y < R;
}
void countMirrors(vector<vector<pt>> &parent, int &ans,pt v1, pt cur){
    if(parent[cur.Y][cur.X]==cur){
        // origin
        return;
    }
    pt v2 = parent[cur.Y][cur.X]-cur;
    ans+=!dot(v1,v2);
    countMirrors(parent,ans,v2,parent[cur.Y][cur.X]);
}
struct State{
    int dir;
    pt p;
    State(){}
    State(int d, pt p):dir(d),p(p){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>C>>R;
    vector<string> grid(R);
    pt cow1(-1,-1),cow2;
    for(int r = 0; r < R; ++r){
        string row; cin>>row;
        grid[r]=row;
        for(int c = 0; c < C; ++c){
            if(grid[r][c]=='C'){
                if(cow1.X==-1){
                    cow1 = pt(c,r);
                }else{
                    cow2 = pt(c,r);
                }
            }
        }
    }
    if(C==1 && R==1){
        cout<<"0\n";
        return 0;
    }
    vector<vector<pt>> parent(R,vector<pt>(C,pt(-1,-1)));
    queue<State> q;
    for(int i = 0; i < 4; ++i)
        q.emplace(i,cow1);
    parent[cow1.Y][cow1.X]=cow1;
    while(!q.empty()){
        State cur = q.front(); q.pop();
        if(cur.p==cow2){
            break;
        }
        pt nxt(cur.p.X+dirC[cur.dir],cur.p.Y+dirR[cur.dir]);
        while(inBounds(nxt) && grid[nxt.Y][nxt.X]!='*'){
            if(parent[nxt.Y][nxt.X].X==-1){
                parent[nxt.Y][nxt.X]=cur.p;
                q.emplace(cur.dir,nxt);
            }
            nxt = pt(nxt.X+dirC[cur.dir],nxt.Y+dirR[cur.dir]);
        }
        for(int i = 0; i < 4; ++i){
            nxt = pt(cur.p.X + dirC[i],cur.p.Y + dirR[i]); 
            if(inBounds(nxt) && grid[nxt.Y][nxt.X]!='*' && parent[nxt.Y][nxt.X].X==-1){
                parent[nxt.Y][nxt.X] = cur.p;
                q.emplace(i,nxt);
            }
        }
    }
    int ans = 0;
    countMirrors(parent,ans,parent[cow2.Y][cow2.X]-cow2,cow2);
    cout<<ans<<"\n";
}
/*
7 8
.......
......C
......*
*****.*
....*..
.*..*..
.C*.**.
..*....
*/