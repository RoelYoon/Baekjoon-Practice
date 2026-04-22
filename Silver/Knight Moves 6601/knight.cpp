#include <iostream>
#include <queue>
using namespace std;
struct CD{
    int r;
    int c;
    CD(){}
    CD(int r, int c):r(r),c(c){}
};
struct State{
    CD c;
    int m;
    State(){}
    State(CD c, int m):c(c),m(m){};
};
void convert(string &s, CD &c){
    c.c = s[0]-'a';
    c.r = s[1]-'0'-1;
}
const int dirR[8]{-2,-1,-2,1,2,2,1,-1};
const int dirC[8]{1,2,-1,2,1,-1,-2,-2};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string p1,p2;
    while(cin>>p1>>p2){
        int moves = 0;
        CD c1,c2;
        convert(p1,c1);
        convert(p2,c2);
        bool visited[8][8]{};
        queue<State> q;
        q.emplace(c1,0);
        visited[c1.r][c1.c] = 1;
        while(!q.empty()){
            State head = q.front(); q.pop();
            if(head.c.r == c2.r && head.c.c == c2.c){
                moves = head.m;
                break;
            }
            for(int i = 0; i < 8; ++i){
                int nxtR = head.c.r + dirR[i];
                int nxtC = head.c.c + dirC[i];
                if(nxtR>=0 && nxtR<8 && nxtC>=0 && nxtC<8 && !visited[nxtR][nxtC]){
                    visited[nxtR][nxtC]=1;
                    q.emplace(CD(nxtR,nxtC),head.m+1);
                }
            }
        }
        cout<<"To get from "<<p1<<" to "<<p2<<" takes "<<moves<<" knight moves.\n";
    }
}