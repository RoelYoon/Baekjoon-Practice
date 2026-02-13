#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int dirK[6]{0,0,0,0,-1,1};
const int dirR[6]{0,1,0,-1,0,0};
const int dirC[6]{1,0,-1,0,0,0};
struct CMP{
    int k,r,c,t;
    CMP(){}
    CMP(int k, int r, int c,int t):k(k),r(r),c(c),t(t){}
    bool operator==(const CMP &o) const {
        return k==o.k && r==o.r && c==o.c;
    }
};
int K,R,C;
inline bool inBounds(CMP cmp){
    return cmp.k>=0 && cmp.k<K && cmp.r>=0 && cmp.r<R && cmp.c>=0 && cmp.c<C;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        cin>>K>>R>>C;
        if(K==0 && R==0 && C==0){
            break;
        }
        vector<vector<vector<char>>> cube(K,vector<vector<char>>(R,vector<char>(C)));
        CMP start,end;
        for(int i = 0; i < K; ++i){
            for(int r = 0; r < R; ++r){
                string s; cin>>s;
                for(int c = 0; c < C; ++c){
                    cube[i][r][c] = s[c];
                    if(s[c]=='S'){
                        start = CMP(i,r,c,0);
                    }else if(s[c]=='E'){
                        end = CMP(i,r,c,0);
                    }
                }
            }
        }
        vector<vector<vector<bool>>> visited(K,vector<vector<bool>>(R,vector<bool>(C)));
        queue<CMP> q;
        q.push(start);
        visited[start.k][start.r][start.c]=1;
        int time = -1;
        while(!q.empty()){
            CMP cur = q.front(); q.pop();
            if(cur==end){
                time = cur.t;
                break;
            }
            for(int i = 0; i < 6; ++i){
                CMP nxt(cur.k+dirK[i], cur.r+dirR[i], cur.c+dirC[i], cur.t+1);
                if(inBounds(nxt) && cube[nxt.k][nxt.r][nxt.c]!='#' && !visited[nxt.k][nxt.r][nxt.c]){
                    q.push(nxt);
                    visited[nxt.k][nxt.r][nxt.c]=1;
                }
            }
        }
        if(time==-1){
            cout<<"Trapped!\n";
        }else{
            cout<<"Escaped in "<<time<<" minute(s).\n";
        }
    }
}
