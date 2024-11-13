#include <iostream>
using namespace std;
int dir[4][2]{{-1,-1},{-1,1},{1,-1},{1,1}}; //TL,TR,BL,BR
int diagonal[4][750][750]{};
int R, C;
bool mine[750][750];
inline bool inBounds(int r, int c){
    return r>=0 && r<R && c>=0 && c<C;
}
int diagonalCount(int d, int r, int c){
    if(!inBounds(r,c)) return 0;
    if(diagonal[d][r][c]) return diagonal[d][r][c];
    if(!mine[r][c]) return 0;
    return diagonal[d][r][c]=mine[r][c]+diagonalCount(d,r+dir[d][0],c+dir[d][1]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C;
    for(int r=0; r<R; ++r){
        string s; cin>>s;
        for(int c=0 ; c<C; ++c)
            mine[r][c]=s[c]-48;
    }
    for(int r=0; r<R; ++r)
        for(int c=0 ; c<C; ++c)
            for(int i = 0; i < 4; ++i)
                diagonalCount(i,r,c);
    int maxD=0;
    for(int r=0; r<=R/2; ++r){
        for(int c=0; c<C; ++c){
            int sizeLim=min(diagonal[2][r][c],diagonal[3][r][c]);
            for(int size = 1; size<=sizeLim; ++size){
                int nr=r+(size-1)*2;
                if(!inBounds(nr,c)) break;
                if(diagonal[0][nr][c]>=size && diagonal[1][nr][c]>=size) maxD=max(maxD,size);
            }
        }
    }
    cout<<maxD<<"\n";
}