#include <iostream>
#include <vector>
using namespace std;
int R,C,k;
struct CD{
    int row;
    int col;
    CD(int r, int c):row(r),col(c){};
    CD():row(-1),col(-1){};
    bool operator==(const CD&other)const{
        return other.row==row && other.col==col;
    }
};
const int dirR[3]{0,1,0};
const int dirC[3]{-1,0,1};
CD findRep(vector<vector<CD>> &unions,CD head){
    if(unions[head.row][head.col]==head)
        return head;
    CD rep = findRep(unions,unions[head.row][head.col]);
    unions[head.row][head.col] = rep;
    return rep;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>R>>C>>k;
    bool free[1005][1005];
    int unionSize[1005][1005];
    vector<vector<CD>> unions(1005,vector<CD>(1005));
    for(int r = 0; r < R; r++){
        string s; cin>>s;
        for(int c = 0; c < C; c++){
            free[r][c]=s[c]=='.';
            unionSize[r][c]=1;
        }
    }
    for(int r = R-1; r >= 0; r--){
        for(int c = 0; c < C; c++){
            if(!free[r][c]){continue;}
            CD cur(r,c);
            if(unions[r][c].row==-1){
                //uninitialized union
                unions[r][c]=cur;
                unionSize[r][c]=1;
            }
            CD curHead = findRep(unions,cur);
            for(int i = 0; i < 3; i++){
                CD nxt(r+dirR[i],c+dirC[i]);
                if(!free[nxt.row][nxt.col]){continue;}
                if(nxt.row < R && nxt.row >= 0 && nxt.col < C && nxt.col >= 0){
                    CD nxtHead = unions[nxt.row][nxt.col].row==-1?nxt:findRep(unions,nxt);
                    if(!(nxtHead==curHead)){
                        unions[nxtHead.row][nxtHead.col]=curHead;
                        unionSize[curHead.row][curHead.col]+=unionSize[nxtHead.row][nxtHead.col];
                    }
                }
            }
            if(unionSize[curHead.row][curHead.col]>=k){
                cout<<r+1<<"\n";
                return 0;
            }
        }
    }
    cout<<-1<<"\n";
}