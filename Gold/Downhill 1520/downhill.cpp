#include <iostream>
#include <unordered_map>
using namespace std;
struct State{
    int r,c,h;
    State(){}
    State(int r, int c, int h):r(r),c(c),h(h){}
    bool operator==(const State &k) const {
        return r==k.r && c==k.c && h==k.h;
    }
    struct Hash{
        size_t operator()(const State &k) const {
            return hash<int>{}(k.r)^(hash<int>{}(k.c)^33)^hash<int>{}(k.h);
        }
    };
};
int R,C;
int height[500][500];
int dr[4]{0,1,0,-1},dc[4]{1,0,-1,0};
unordered_map<State,int,State::Hash> DP;
int count(int r, int c, int h){
    if(!(r>=0&&r<R&&c>=0&&c<C) || height[r][c]>=h) return 0;
    if(r==R-1 && c==C-1) return 1;
    State k(r,c,h);
    unordered_map<State,int,State::Hash>::iterator dp = DP.find(k);
    if(dp!=DP.end()) return dp->second;
    h=min(h,height[r][c]);
    int cnt = 0;
    for(int i = 0; i < 4; ++i){
        cnt+=count(r+dr[i],c+dc[i],h);
    }
    return DP[k]=cnt;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C;
    for(int r=0; r<R; ++r){
        for(int c=0; c<C; ++c){
            cin>>height[r][c];
        }
    }
    cout<<count(0,0,1e9)<<"\n";
}