#include <iostream>
#define ll long long
using namespace std;
int board[105][105];
int S;
ll DP[105][105]{};
ll count(int r, int c){
    if(r>=S || c>=S) return 0;
    if(r==S-1 && c==S-1) return 1;
    if(!board[r][c]) return 0;
    if(DP[r][c]) return DP[r][c];
    return DP[r][c]=count(r+board[r][c],c)+count(r,c+board[r][c]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>S;
    for(int r=0; r<S;++r)
        for(int c=0;c<S;++c)
            cin>>board[r][c];
    cout<<count(0,0)<<"\n";
}