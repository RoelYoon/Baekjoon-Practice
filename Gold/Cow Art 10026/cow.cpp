#include <iostream>
#include <vector>
#include <string>
#include <complex>
#define pt complex<int>
#define ROW real()
#define COL imag()
using namespace std;
int n;
const pt dir[4]{pt(1,0),pt(0,1),pt(-1,0),pt(0,-1)};
void DFSH(vector<string> &grid, char type, pt head){
    if(grid[head.ROW][head.COL]!=type) return;
    grid[head.ROW][head.COL]='x';
    for(int i = 0; i < 4; ++i){
        pt nxt = head+dir[i];
        if(nxt.ROW >= 0 && nxt.ROW < n && nxt.COL>=0 && nxt.COL < n){
            DFSH(grid,type,nxt);
        }
    }
}
void DFSC(vector<string> &grid, char type, pt head){
    if(grid[head.ROW][head.COL]!=type){
        if(!(type=='R' && grid[head.ROW][head.COL]=='G' || 
        type=='G' && grid[head.ROW][head.COL]=='R')){
            return;
        }
    };
    grid[head.ROW][head.COL]='x';
    for(int i = 0; i < 4; ++i){
        pt nxt = head+dir[i];
        if(nxt.ROW >= 0 && nxt.ROW < n && nxt.COL>=0 && nxt.COL < n){
            DFSC(grid,type,nxt);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n; 
    vector<string> grid(n),grid2(n);
    for(int i = 0; i < n; ++i){
        cin>>grid[i];
        grid2[i]=grid[i];
    }
    int humanCnt = 0;
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            if(grid[r][c] != 'x'){
                ++humanCnt;
                DFSH(grid,grid[r][c],pt(r,c));
            }
        }
    }
    int cowCnt = 0;
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            if(grid2[r][c] != 'x'){
                ++cowCnt;
                DFSC(grid2,grid2[r][c],pt(r,c));
            }
        }
    }
    cout<<humanCnt<<" "<<cowCnt<<"\n";
}