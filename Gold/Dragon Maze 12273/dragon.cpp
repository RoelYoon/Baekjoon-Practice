#include <iostream>
#include <complex>
#include <set>
#define pt complex<int>
#define X real()
#define Y imag()
using namespace std;
struct State{
    int d,p;
    pt pos;
    State(){}
    State(int d, int p, pt pos):d(d),p(p),pos(pos){}
    bool operator==(const State &k) const {
        return d==k.d && p==k.p && pos==k.pos;
    }
    bool operator<(const State &k) const {
        if(d==k.d){
            if(p==k.p){
                if(pos.X==k.pos.X){
                    return pos.Y<k.pos.Y;
                }return pos.X<k.pos.X;
            }
            return p>k.p;
        }return d<k.d;
    }
};
const int dx[4]{0,-1,0,1},dy[4]{1,0,-1,0};
int R,C, sx,sy,ex,ey;
int maze[101][101];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    for(int t = 0; t < T; ++t){
        cin>>R>>C>>sx>>sy>>ex>>ey;
        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){
                cin>>maze[r][c];
            }
        }
        State dist[101][101];
        for(int r=0; r<R; ++r){
            for(int c=0; c<C; ++c){
                dist[r][c].d=1e9;
                dist[r][c].p=-1;
                dist[r][c].pos=pt(r,c);
            }
        }
        dist[sx][sy].d=0;
        dist[sx][sy].p=maze[sx][sy];
        set<State> pq{dist[sx][sy]}; 
        while(!pq.empty()){
            State s = *pq.begin();
            pq.erase(pq.begin());
            if(maze[s.pos.X][s.pos.Y]==-1) continue;
            for(int i=0; i < 4; ++i){
                int nx=s.pos.X+dx[i],ny=s.pos.Y+dy[i];
                if(!(nx>=0&&nx<R&&ny>=0&&ny<C) || maze[nx][ny]==-1) continue;
                State ns(s.d+1,s.p+maze[nx][ny],{nx,ny});
                if(!(dist[nx][ny]<ns)){
                    set<State>::iterator oldQ = pq.find(dist[nx][ny]);
                    if(oldQ!=pq.end())
                        pq.erase(oldQ);
                    dist[nx][ny]=ns;
                    pq.insert(ns);
                }
            }
        }
        cout<<"Case #"<<t+1<<": "<<(dist[ex][ey].p==-1?"Mission Impossible.":to_string(dist[ex][ey].p))<<"\n";
    }
}
/*
1
4 4
0 2 3 2
-1 1 1 2
1 1 1 1
2 3 -1 1
1 1 1 1

1
1 1
0 0 0 0
-1 

1
1 2
0 0 0 1
1 1
*/