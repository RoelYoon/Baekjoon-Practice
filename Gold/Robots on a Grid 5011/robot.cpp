#include <iostream>
#define ll long long
#define PM 2147483647
using namespace std;
const int dr[4]{0,1,0,-1},dc[4]{1,0,-1,0};
int S;
char board[1000][1000];
bool visited[1000][1000]{};
ll DP[1000][1000];
bool possible=0;
ll count(int r, int c){
    if(!(r>=0&&r<S&&c>=0&&c<S) || board[r][c]=='#') return 0;
    if(r==S-1 && c==S-1) {possible=1;return 1;}
    if(DP[r][c]!=-1) return DP[r][c];
    ll cnt = 0;
    for(int i = 0; i < 2; ++i){
        cnt+=(count(r+dr[i],c+dc[i])%PM);
        cnt%=PM;
    }
    return DP[r][c]=cnt%PM;
}
bool reachable(int r, int c){
    if(!(r>=0&&r<S&&c>=0&&c<S) || board[r][c]=='#' || visited[r][c]) return 0;
    visited[r][c]=1;
    if(r==S-1 && c==S-1) return 1;
    for(int i = 0; i < 4; ++i)
        if(reachable(r+dr[i],c+dc[i]))
            return 1; 
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>S;
    for(int r = 0; r<S; ++r){
        for(int c=0; c<S; ++c){
            cin>>board[r][c];
            DP[r][c]=-1;
        }
    }
    ll cnt = count(0,0);
    cout<<(possible?to_string(cnt):(reachable(0,0)?"THE GAME IS A LIE":"INCONCEIVABLE"))<<"\n";
}
/*
7
......#
#####..
.#.....
.#...#.
.#.....
.#..###
.#.....
*/