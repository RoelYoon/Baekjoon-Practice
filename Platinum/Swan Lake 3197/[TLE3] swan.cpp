#include <cstdio>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX 1505
#define UNSET_ANS 1000000000
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
const int dirR[4]{0,1,0,-1}, dirC[4]{1,0,-1,0};
CD findUnion(vector<vector<CD>> &unionFind, CD head){
    if(unionFind[head.row][head.col]==head)
        return head;
    CD parent = findUnion(unionFind,unionFind[head.row][head.col]);
    unionFind[head.row][head.col]=parent;
    return parent;
}
void GreedyFollow(vector<vector<char>> &lake, vector<vector<CD>> &unionFind,unordered_map<CD,vector<CD>,CD::Hash> &unionConnections, vector<vector<State>> &state, bool visited[MAX][MAX], int &minDepth, CD& target, int depth,CD head){
    visited[head.row][head.col]=1;
    printf("(%d, %d)\n",head.row,head.col);
    bool isIce = lake[head.row][head.col]=='X'; 
    CD headUnion = isIce ? CD() : findUnion(unionFind,head);
    vector<CD> nxtConnections = isIce ? vector<CD>() : unionConnections[headUnion];
    if(isIce){
        for(int i = 0; i < 4; i++){
            int nxtR = head.row+dirR[i];
            int nxtC = head.col+dirC[i];
            CD nxt(nxtR,nxtC);
            if(nxtR >= 0 && nxtR < R && nxtC >=0 && nxtC < C && !visited[nxtR][nxtC])
                nxtConnections.push_back(nxt);
        }
    }else{
        visited[head.row][head.col]=0;
        if(headUnion==target){
            minDepth=depth;
            return;
        }
        if(visited[headUnion.row][headUnion.col]){return;}
        visited[headUnion.row][headUnion.col]=1;
    }
    sort(nxtConnections.begin(),nxtConnections.end(),[&state](const CD &a, const CD &b)->bool{
        return state[a.row][a.col].depth < state[b.row][b.col].depth;
    });
    for(int i = 0; i < nxtConnections.size(); i++){
        //printf("(%d,%d)\n",nxtConnections[i].row,nxtConnections[i].col);
        if(!visited[nxtConnections[i].row][nxtConnections[i].col])
            GreedyFollow(lake,unionFind,unionConnections,state,visited,minDepth,target,max(depth,state[head.row][head.col].depth),nxtConnections[i]);
        if(minDepth!=UNSET_ANS)
            return;
    }
}
void assignUnion(vector<vector<char>> &lake, vector<vector<CD>> &unionFind,vector<vector<vector<CD>>> &unionConnections, CD rep){
    queue<CD> q; q.push(rep); 
    vector<vector<bool>> visited(R,vector<bool>(C,false));
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
                    unionConnections[rep.row][rep.col].push_back(CD(nxtR,nxtC));
                }
            }
        }
    }
}
void assignDepth(vector<vector<char>> &lake, vector<vector<CD>> &unionFind,vector<CD> &unionConnections, vector<vector<State>> &state, CD sourceUnion){
    struct Q_Element{
        CD cd; 
        int depth=0;
        Q_Element(CD cd, int d):cd(cd),depth(d){};
    };
    queue<Q_Element> q;
    bool visited[MAX][MAX]{};
    for(int i = 0; i < unionConnections.size(); i++){
        q.push(Q_Element(unionConnections[i],0));
        visited[unionConnections[i].row][unionConnections[i].col]=1;
    }
    while(!q.empty()){
        Q_Element top = q.front(); q.pop();
        if(lake[top.cd.row][top.cd.col]!='X'){continue;}
        State s(top.depth+1,sourceUnion);
        if((s.depth < state[top.cd.row][top.cd.col].depth || state[top.cd.row][top.cd.col].depth==-1)){
            state[top.cd.row][top.cd.col]=s;
            unionFind[top.cd.row][top.cd.col]=sourceUnion;
        }
        for(int i = 0; i < 4; i++){
            int nxtR = top.cd.row+dirR[i];
            int nxtC = top.cd.col+dirC[i];
            if(nxtR >= 0 && nxtR < R && nxtC >=0 && nxtC < C && !visited[nxtR][nxtC]){
                q.push(Q_Element(CD(nxtR,nxtC),state[top.cd.row][top.cd.col].depth));
                visited[nxtR][nxtC]=1;
            }
        }
    }
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
    /* Allocating all of these on stack causes stack overflow.
    Change to heap-allocated static arrays if MLE (or unordered_map implementation) */
    vector<vector<char>> lake(R);
    vector<vector<CD>> unionFind(R,vector<CD>(C));
    vector<vector<State>> state(R,vector<State>(C));
    CD S1, S2;
    for(int r = 0; r < R; r++){
        char cs[MAX]; scanf("%1505s",cs);
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
    bool depthAssigned[MAX][MAX]{};
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if(lake[r][c]!='X' && unionFind[r][c].row == -1){
                CD rep(r,c);
                unionConnections.insert({rep,vector<CD>()});
                assignUnion(lake,unionFind,unionConnections[rep],rep);
                unionReps.push_back(rep);
                if(!depthAssigned[rep.row][rep.col]){
                    depthAssigned[rep.row][rep.col]=true;
                    assignDepth(lake,unionFind,unionConnections[rep],state,rep);
                }
            }
        }
    }
    int minDepth = UNSET_ANS;
    CD targetUnion = findUnion(unionFind,S2);
    bool visited[MAX][MAX]{};
    GreedyFollow(lake,unionFind,unionConnections,state,visited,minDepth,targetUnion,0,S1);
    printf("%d\n",minDepth);
}
/*
14 3
L..
...
XXX
XXX
XXX
XXX
XXX
XXX
XXX
XXX
XXX
XXX
...
..L
*/