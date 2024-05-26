#include <iostream>
#include <vector>
#include <queue>
#define MAX 1505
using namespace std;
struct CD{
    int r; 
    int c;
    CD():r(-1),c(-1){}
    CD(int r, int c):r(r),c(c){}
    bool operator==(const CD& o) const {
        return o.r==r && o.c == c;
    }
    bool operator!=(const CD& o) const {
        return !(o==*this);
    }
};
class UnionFind{
    private:
    vector<vector<CD>> parent;
    vector<vector<int>> ranks;
    public: 
    UnionFind(int R, int C){
        parent=vector<vector<CD>>(R,vector<CD>(C));
        ranks=vector<vector<int>>(R,vector<int>(C));
        for(int r = 0; r < R; r++){
            for(int c = 0; c < C; c++){
                parent[r][c]=CD(r,c);
            }
        }
    }
    CD find(CD cd){
        if(parent[cd.r][cd.c]==cd){return cd;}
        return parent[cd.r][cd.c]=find(parent[cd.r][cd.c]);
    }
    void merge(CD a, CD b){
        a = find(a);
        b = find(b);
        if(ranks[a.r][a.c] > ranks[b.r][b.c]){
            parent[b.r][b.c]=a;
        }else if(ranks[a.r][a.c] < ranks[b.r][b.c]){
            parent[a.r][a.c]=b;
        }else{
            parent[a.r][a.c]=b;
            ranks[b.r][b.c]++;
        }
    }
};
int R,C;
const int dirR[4]{-1,0,1,0};
const int dirC[4]{0,1,0,-1};
inline bool inBounds(int r, int c){
    return r < R && r >= 0 && c < C && c >= 0; 
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C;
    char lake[MAX][MAX];
    queue<CD> q;
    UnionFind unionFind(R,C);
    bool visited[MAX][MAX]{};
    CD S1,S2;
    for(int r = 0; r < R; r++){
        string s; cin>>s;
        for(int c = 0; c < C; c++){
            lake[r][c]=s[c];
            if(s[c]!='X'){
                q.push(CD(r,c));
                visited[r][c]=1;
            }
            if(s[c]=='L'){
                if(S1.r==-1){
                    S1=CD(r,c);
                }else{
                    S2=CD(r,c);
                }
            }
        }
    }
    int days = 0;
    while(unionFind.find(S1)!=unionFind.find(S2)){
        days++;
        CD qEnd = q.back();
        CD cur; 
        while(cur!=qEnd){
            cur = q.front(); q.pop();
            if(lake[cur.r][cur.c]=='X')lake[cur.r][cur.c]='.';
            for(int i = 0; i < 4; i++){
                CD nxt(cur.r+dirR[i],cur.c+dirC[i]);
                if(!inBounds(nxt.r,nxt.c)){continue;}
                if(!visited[nxt.r][nxt.c]){
                    visited[nxt.r][nxt.c]=1;
                    q.push(nxt);
                }
                if(lake[nxt.r][nxt.c]!='X'){
                    unionFind.merge(cur,nxt);
                }
            }
        }
    }
    cout<<days-1<<"\n";
}