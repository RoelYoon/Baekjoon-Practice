#include <cstdio>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#define MAX 1505
using namespace std;
struct CD{
    int row;
    int col;
    CD():row(-1),col(-1){};
    CD(int r, int c):row(r),col(c){};
    bool operator==(const CD &other)const{
        return row==other.row && col == other.col;
    }
    bool operator!=(const CD &other)const{
        return !(*this==other);
    }
    struct Hash{
        size_t operator()(const CD &a)const{
            return hash<int>{}(a.row) ^ hash<int>{}(a.col);
        }
    };
};
struct State{
    int depth; 
    CD saver; 
    State():depth(-1){};
    State(int d, CD s):depth(d),saver(s){};
};
int R, C;
const int dirR[4]{-1,0,1,0}, dirC[4]{0,1,0,-1};
CD findUnion(vector<vector<CD>> &unionFind, CD head){
    if(unionFind[head.row][head.col]==head)
        return head;
    CD parent = findUnion(unionFind,unionFind[head.row][head.col]);
    unionFind[head.row][head.col]=parent;
    return parent;
}
void mergeUnions(vector<vector<char>> &lake, vector<vector<CD>> &unionFind,vector<CD> &unionConnections, CD rep){

}
void assignUnion(vector<vector<char>> &lake, vector<vector<CD>> &unionFind,vector<CD> &unionConnections, CD rep){
    queue<CD> q; q.push(rep);
    bool visited[MAX][MAX]{};
    visited[rep.row][rep.col]=1;
    while(!q.empty()){
        CD top = q.front(); q.pop();
        if(unionFind[top.row][top.col].row==-1){
            unionFind[top.row][top.col] = rep;
        }
        for(int i = 0; i < 4; i++){
            int nxtR = top.row+dirR[i];
            int nxtC = top.col+dirC[i];
            if(nxtR >= 0 && nxtR < R && nxtC >=0 && nxtC < C && !visited[nxtR][nxtC]){
                if(lake[nxtR][nxtC]!='X'){
                    q.push(CD(nxtR,nxtC));
                    visited[nxtR][nxtC]=1;
                }else{
                    unionConnections.push_back(CD(nxtR,nxtC));
                }
            }
        }
    }
}
int main(){
    freopen("in","r",stdin);
    scanf("%d%d",&R,&C);
    vector<vector<char>> lake(R);
    vector<vector<CD>> unionFind(R,vector<CD>(C));
    vector<vector<State>> state(R,vector<State>(C));
    CD S1, S2;
    for(int r = 0; r < R; r++){
        char cs[MAX]; scanf("%1500s",cs);
        string s=cs;
        for(int c = 0; c < C; c++){
            lake[r].push_back(s[c]);
            if(lake[r][c]=='L'){
                if(S1.row==-1){
                    S1 = CD(r,c);
                }else{
                    S2 = CD(r,c);
                }
            }
        }
    }
    unordered_map<CD,vector<CD>,CD::Hash> unionConnections;
    vector<CD> unionReps;
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if((lake[r][c]=='.' || lake[r][c]=='L') && unionFind[r][c].row == -1){
                //if water block and union is uninitialized
                CD rep(r,c);
                unionConnections.insert({rep,vector<CD>()});
                assignUnion(lake,unionFind,unionConnections[rep],rep);
                unionReps.push_back(rep);
            }
        }
    }
    int minDays = 0;
    struct UnionPair{
        CD unionRepA;
        CD unionRepB;
        UnionPair(CD a, CD b):unionRepA(a),unionRepB(b){};
    };
    while(findUnion(unionFind,S1)!=findUnion(unionFind,S2)){
        for(int i = 0; i < unionReps.size(); i++){
            for(int j = 0; j < unionConnections[unionReps[i]].size(); j++){
                lake[unionConnections[unionReps[i]][j].row][unionConnections[unionReps[i]][j].col]='.';
                unionFind[unionConnections[unionReps[i]][j].row][unionConnections[unionReps[i]][j].col]=unionReps[i];
            }
        }
        vector<UnionPair> toMerge;
        for(int i = 0; i < unionReps.size(); i++){
            if(findUnion(unionFind,unionReps[i])!=unionReps[i]){continue;}
            vector<CD> newConnections;
            unordered_set<CD,CD::Hash> mergedUnions;
            bool visited[MAX][MAX]{};
            for(int j = 0; j < unionConnections[unionReps[i]].size(); j++){
                for(int k = 0; k < 4; k++){
                    int nxtR = unionConnections[unionReps[i]][j].row + dirR[k];
                    int nxtC = unionConnections[unionReps[i]][j].col + dirC[k];
                    if(!(nxtR >= 0 && nxtR < R && nxtC >=0 && nxtC < C && !visited[nxtR][nxtC])){continue;}
                    visited[nxtR][nxtC]=1;
                    CD nxt(nxtR,nxtC);
                    if(lake[nxtR][nxtC]=='X'){
                        newConnections.push_back(nxt);
                    }else{
                        CD nxtUnion = findUnion(unionFind,nxt); 
                        if(nxtUnion!=unionReps[i] && mergedUnions.find(nxtUnion)==mergedUnions.end()){
                            toMerge.push_back(UnionPair(nxtUnion,unionReps[i]));
                            mergedUnions.insert(nxtUnion);
                        }
                    }
                }
            }
            unionConnections[unionReps[i]]=newConnections;
        }
        //vector<CD> newUnionReps;
        for(int i = 0; i < toMerge.size(); i++){
            CD union1 = findUnion(unionFind,toMerge[i].unionRepA);
            CD union2 = findUnion(unionFind,toMerge[i].unionRepB);
            if(union1==union2){continue;}
            unionFind[union1.row][union1.col]=union2;
            for(int j = 0; j < unionConnections[union1].size(); j++){
                unionConnections[union2].push_back(unionConnections[union1][j]);
            }
        }
        //unionReps = newUnionReps;
        minDays++;
    }
    printf("%d",minDays);
}