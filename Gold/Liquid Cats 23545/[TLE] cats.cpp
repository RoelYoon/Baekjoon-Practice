#include <iostream>
#include <unordered_map>
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
    struct Hash{
        size_t operator()(const CD &a)const{
            static const size_t ROEL_HASH = hash<string>{}("Roel's Hash"); // added so inverse pairs don't collide
            return hash<int>{}(a.row) ^ (hash<int>{}(a.col) ^ ROEL_HASH);
        }
    };
};
struct LinkedEdges{
    vector<CD> edges;
    LinkedEdges *nxt=nullptr;
};
const int dirR[5]{0,-1,-1,-1,0};
const int dirC[5]{-1,-1,1,1,1};
CD findRep(unordered_map<CD,CD,CD::Hash> &unions,CD head){
    if(unions[head]==head)
        return head;
    CD rep = findRep(unions,unions[head]);
    unions[head] = rep;
    return rep;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>R>>C>>k;
    bool free[1005][1005];
    int unionSize[1005][1005];
    unordered_map<CD,CD,CD::Hash> unions;
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
            if(unions.find(cur)==unions.end()){
                //uninitialized union
                unions.insert({cur,cur});
                unionSize[cur.row][cur.col]=1;
            }
            CD curHead = findRep(unions,cur);
            for(int i = 0; i < 5; i++){
                CD nxt(r+dirR[i],c+dirC[i]);
                if(!free[nxt.row][nxt.col]){continue;}
                if(nxt.row < R && nxt.row >= 0 && nxt.col < C && nxt.col >= 0){
                    CD nxtHead = unions.find(nxt)!=unions.end()?findRep(unions,nxt):nxt;
                    if(!(nxtHead==curHead)){
                        unions[nxtHead]=curHead;
                        unionSize[curHead.row][curHead.col]+=unionSize[nxtHead.row][nxtHead.col];
                    }
                }
            }
            if(unionSize[curHead.row][curHead.col]>=k){
                cout<<r<<"\n";
                return 0;
            }
        }
    }
    cout<<-1<<"\n";
}