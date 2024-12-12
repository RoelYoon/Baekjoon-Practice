#include <iostream>
#define ll long long
using namespace std;
const int dr[4]{0,1,0,-1},dc[4]{1,0,-1,0};
char farm[100][100];
int R,C,T,R1,C1,R2,C2;
ll DP[100][100][15];
ll count(int r, int c, int t){
    if(!(r>=0&&r<R&&c>=0&&c<C) || farm[r][c]=='*' || t>T) return 0;
    if(r==R2 && c==C2 && t==T) return 1;
    if(DP[r][c][t]!=-1) return DP[r][c][t];
    ll cnt = 0;
    for(int i=0; i < 4; ++i){
        cnt+=count(r+dr[i],c+dc[i],t+1);
    }
    return DP[r][c][t]=cnt;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C>>T;
    for(int r=0; r<R; ++r){
        for(int c=0; c<C; ++c){
            cin>>farm[r][c];
            for(int t=0; t<T; ++t)
                DP[r][c][t]=-1;
        }
    }
    cin>>R1>>C1>>R2>>C2;
    --R1,--C1,--R2,--C2;
    cout<<count(R1,C1,0)<<"\n";
}
/*
4 5 6
...*.
...*.
.....
.....
1 3 1 5

3 3 10
.*.
.*.
...
1 1 3 3
*/