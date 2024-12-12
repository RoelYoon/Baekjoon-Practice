#include <iostream>
#define ll long long
using namespace std;
int dirR[8]{-1,-1,-1,0,1,1,1,0},dirC[8]{-1,0,1,1,1,0,-1,-1};
int R,C,L;
string word;
char board[200][200];
ll DP[200][200][100];
ll count(int r, int c, string &s){
    if(!(r>=0 && r<R && c>=0 && c<C) || s.size()>L || board[r][c]!=word[s.size()]) return 0;
    if(DP[r][c][s.size()]!=-1) {return DP[r][c][s.size()];}
    s.push_back(board[r][c]);
    if(s.size()==word.size()){
        s.pop_back();
        return DP[r][c][s.size()]=1;
    }
    ll cnt = 0;
    for(int i = 0; i < 8; ++i){
        cnt+=count(r+dirR[i],c+dirC[i],s);
    }
    s.pop_back();
    return DP[r][c][s.size()]=cnt;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C>>L;
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            cin>>board[r][c];
            for(int i = 0; i < 100; ++i){
                DP[r][c][i]=-1;
            }
        }
    }
    cin>>word;
    ll cnt = 0;
    string s = "";
    for(int r = 0; r < R; ++r){
        for(int c = 0; c < C; ++c){
            if(board[r][c]==word[0]){
                cnt+=count(r,c,s);
            }
        }
    }
    cout<<cnt<<"\n";
}
/*
3 4 2
ERAT
ATSR
AUTT
TT
*/