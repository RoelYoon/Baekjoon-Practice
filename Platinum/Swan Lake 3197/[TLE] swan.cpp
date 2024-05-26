#include <vector>
#include <queue>
#include <cstdio>
#include <string>
using namespace std;
struct CD{
    int row; 
    int col;
    CD():row(-1),col(-1){};
    CD(int r, int c):row(r),col(c){};
    bool operator==(CD &other){
        return row==other.row && col == other.col;
    }
    bool operator!=(CD &other){
        return !(*this==other);
    }
    friend bool operator!=(CD a, CD b){
        return !(a==b);
    }
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
    queue<Q_Element> q; vector<vector<bool>> visited(R,vector<bool>(C));
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
void findSwan(vector<vector<char>> &lake, vector<vector<CD>> &unionFind, vector<vector<vector<CD>>> &unionConnections, vector<vector<State>> &state, int &minDepth, CD S, CD targetS){
    struct Q_Element{
        CD cd; 
        int depth=0;
        Q_Element(CD cd, int d):cd(cd),depth(d){};
    };
    queue<Q_Element> q;
    vector<vector<bool>> visited(R,vector<bool>(C));
    for(int i = 0; i < unionConnections[S.row][S.col].size(); i++){
        q.push(Q_Element(unionConnections[S.row][S.col][i],state[unionConnections[S.row][S.col][i].row][unionConnections[S.row][S.col][i].col].depth));
        visited[unionConnections[S.row][S.col][i].row][unionConnections[S.row][S.col][i].col]=1;
    }
    visited[S.row][S.col]=1;
    while(!q.empty()){
        CD top = q.front().cd; int d = q.front().depth; q.pop();
        for(int i = 0; i < 4; i++){
            int nxtR = top.row+dirR[i];
            int nxtC = top.col+dirC[i];
            CD nxt(nxtR,nxtC);
            if(!(nxtR >= 0 && nxtR < R && nxtC >=0 && nxtC < C)){continue;}
            CD nxtRep = lake[nxtR][nxtC]=='X'?CD(0,0):findUnion(unionFind,nxt);
            if(!visited[nxtR][nxtC] && (lake[nxtR][nxtC]!='X' ? !visited[nxtRep.row][nxtRep.col] : 1)){
                if(lake[nxtR][nxtC]=='X'){
                    q.push(Q_Element(nxt,max(d,state[nxtR][nxtC].depth)));
                    visited[nxtR][nxtC]=1;
                }else if(nxtRep==targetS){
                    minDepth = min(minDepth,d);
                }else{
                    for(int i = 0; i < unionConnections[nxtR][nxtC].size(); i++){
                        q.push(Q_Element(unionConnections[nxtR][nxtC][i],max(d,state[unionConnections[nxtR][nxtC][i].row][unionConnections[nxtR][nxtC][i].col].depth)));
                        visited[unionConnections[nxtR][nxtC][i].row][unionConnections[nxtR][nxtC][i].col]=1;
                    }
                    visited[nxtRep.row][nxtRep.col]=1;
                }
            }
        }
    }

}
int main(){
    //freopen("in","r",stdin);
    scanf("%d%d",&R,&C);
    vector<vector<char>> lake(R);
    vector<vector<CD>> unionFind(R,vector<CD>(C));
    vector<vector<State>> state(R,vector<State>(C));
    CD S1, S2;
    for(int r = 0; r < R; r++){
        char cs[1500]; scanf("%1500s",cs);
        string s=cs; //cin>>s;
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
    vector<vector<vector<CD>>> unionConnections(R,vector<vector<CD>>(C));
    vector<vector<bool>> depthAssigned(R,vector<bool>(C));
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if((lake[r][c]=='.' || lake[r][c]=='L') && unionFind[r][c].row == -1){
                //if water block and union is uninitialized
                assignUnion(lake,unionFind,unionConnections,CD(r,c));
                CD rep = findUnion(unionFind,CD(r,c));
                if(!depthAssigned[rep.row][rep.col]){
                    depthAssigned[rep.row][rep.col]=true;
                    assignDepth(lake,unionFind,unionConnections[rep.row][rep.col],state,rep);
                }
            }
        }
    }
    int minDepth = 1000000000;
    findSwan(lake,unionFind,unionConnections,state,minDepth,findUnion(unionFind,S1),findUnion(unionFind,S2));
    printf("%d\n",minDepth);
}