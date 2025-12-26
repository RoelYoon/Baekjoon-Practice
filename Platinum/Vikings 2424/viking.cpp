#include <iostream>
#include <vector>
#include <queue>
#include <complex>
#include <utility>
#include <algorithm>
#define pt complex<int>
#define ROW real()
#define COL imag()
#define INF 1e9
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    vector<int> st;
    vector<bool> lazy;
    vector<int> upd;
    int n;
    void propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]=min(st[p],upd[p]);
            if(L!=R){
                lazy[LC(p)] = lazy[RC(p)] = 1;
                upd[LC(p)] = min(upd[LC(p)],upd[p]);
                upd[RC(p)] = min(upd[RC(p)],upd[p]);
            }
            lazy[p]=0;
            upd[p]=INF;
        }
    }
    int query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return INF;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return min(query(LC(p), L, mid, QL, QR), query(RC(p), mid+1, R, QL, QR));
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]=min(upd[p],u);
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p), L, mid, QL, QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p] = min(st[LC(p)], st[RC(p)]);
    }
    void build(int p, int L, int R){
        if(L==R){
            st[p] = INF;
            return;
        }
        int mid = (L+R)/2;
        build(LC(p), L, mid);
        build(RC(p), mid+1, R);
        st[p] = min(st[LC(p)], st[RC(p)]);
    }
    public:
    SegmentTree(int n):n(n),st(4*n),lazy(4*n),upd(4*n,INF){
        build(0,0,n-1);
    }
    SegmentTree(){}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int L, int R, int u){
        update(0,0,n-1,L,R,u);
    }
};
int R,C;
const pt dir[4]{{0,1},{1,0},{0,-1},{-1,0}};
inline bool inBounds(pt p){
    return p.ROW>=0 && p.ROW<R && p.COL>=0 && p.COL<C;
}
struct Cell{
    char c;
    int sd;
    int d;
    Cell():d(INF),sd(INF){}
    Cell(char c, int s, int d):c(c),sd(s),d(d){}
};
int block(bool posDir, int mx, vector<int> &Is, int x){
    int pos = lower_bound(Is.begin(), Is.end(), x) - Is.begin();
    if(posDir){
        if(pos==Is.size())
            return mx;
        return Is[pos]-1;
    }else{
        if(!pos)
            return 0;
        return Is[pos-1]+1;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>R>>C;
    vector<vector<Cell>> grid(R,vector<Cell>(C));
    vector<SegmentTree> rowSD(R,SegmentTree(C)), colSD(C,SegmentTree(R));
    vector<vector<int>> rowI(R), colI(C);
    pt Y,V;
    for(int r = 0; r < R; ++r){
        string s; cin>>s;
        for(int c = 0; c < C; ++c){
            grid[r][c].c = s[c];
            if(s[c]=='Y'){
                Y=pt(r,c);
            } else if(s[c]=='V'){
                V=pt(r,c);
            } else if(s[c]=='I'){
                rowI[r].push_back(c);
                colI[c].push_back(r);
            }
        }
    }
    queue<pair<pt,int>> q;
    vector<vector<bool>> visited(R,vector<bool>(C));
    visited[V.ROW][V.COL]=1;
    q.push(make_pair(V,0));
    while(!q.empty()){
        pt p = q.front().first;
        int d = q.front().second; q.pop();
        rowSD[p.ROW].update(p.COL,block(1,C-1,rowI[p.ROW],p.COL),d);
        rowSD[p.ROW].update(block(0,C-1,rowI[p.ROW],p.COL),p.COL,d);
        colSD[p.COL].update(p.ROW,block(1,R-1,colI[p.COL],p.ROW),d);
        colSD[p.COL].update(block(0,R-1,colI[p.COL],p.ROW),p.ROW,d);
        for(int i = 0 ; i < 4; ++i){
            pt nxt = p + dir[i];
            if(inBounds(nxt) && !visited[nxt.ROW][nxt.COL] && grid[nxt.ROW][nxt.COL].c!='I'){
                visited[nxt.ROW][nxt.COL]=1;
                q.push(make_pair(nxt,d+1));
            }
        }
    }
    for(int r = 0; r< R; ++r){
        for(int c=0;c<C;++c){
            if(grid[r][c].c=='I') continue;
            grid[r][c].sd=min(rowSD[r].query(c,c),colSD[c].query(r,r));
            visited[r][c]=0;
        }
    }
    visited[Y.ROW][Y.COL]=1;
    grid[Y.ROW][Y.COL].d=0;
    q.push(make_pair(Y,0));
    while(!q.empty()){
        pt p = q.front().first; 
        int d = q.front().second; q.pop();
        for(int i = 0 ; i < 4; ++i){
            pt nxt = p + dir[i];
            if(inBounds(nxt) && !visited[nxt.ROW][nxt.COL] && grid[nxt.ROW][nxt.COL].c!='I' && (d+1<grid[nxt.ROW][nxt.COL].sd)){
                visited[nxt.ROW][nxt.COL]=1;
                grid[nxt.ROW][nxt.COL].d = d+1;
                q.push(make_pair(nxt,d+1));
                if(grid[nxt.ROW][nxt.COL].c=='T'){
                    cout<<"YES\n";
                    return 0;
                }
            }
        }
    }
    cout<<"NO\n";
}