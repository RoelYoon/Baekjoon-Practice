#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#define MAX 1505
using namespace std;
struct CD{
    int row;
    int col;
    CD():row(-1),col(-1){}
    CD(int r, int c):row(r),col(c){}
    bool operator==(const CD &other) const {
        return other.row==row && other.col==col;
    }
    struct Hash{
        size_t operator()(const CD &a) const {
            static const size_t d = hash<int>{}(55555555);
            return hash<int>{}(a.row) ^ (hash<int>{}(a.col)^d);
        }
    };
};
int R,C;
const int dirR[4]{-1,0,1,0};
const int dirC[4]{0,1,0,-1};
char lake[MAX][MAX];
vector<vector<CD>> unions(MAX,vector<CD>(MAX));
vector<vector<vector<CD>>> unionConnections(MAX,vector<vector<CD>>(MAX));
list<CD> reps; 
CD findRep(CD head){
    if(unions[head.row][head.col]==head)
        return head;
    CD rep = findRep(unions[head.row][head.col]);
    unions[head.row][head.col]=rep;
    return rep;
}
void DFS(vector<vector<bool>> &visited,CD &originRep, CD head){
    if(visited[head.row][head.col]){
        return;
    }
    visited[head.row][head.col]=1;
    if(lake[head.row][head.col]=='X'){
        unionConnections[originRep.row][originRep.col].push_back(head);
    }else{
        unions[head.row][head.col]=originRep;
        for(int i = 0; i < 4; i++){
            CD nxt(head.row+dirR[i],head.col+dirC[i]);
            if(nxt.row < R && nxt.row >= 0 && nxt.col < C && nxt.col >=0){
                DFS(visited,originRep,nxt);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("in","r",stdin);
    cin>>R>>C;
    CD S1, S2;
    for(int r = 0; r < R; r++){
        string s; cin>>s;
        for(int c = 0; c < C; c++){
            lake[r][c]=s[c];
            if(lake[r][c]=='L'){
                if(S1.row==-1){
                    S1=CD(r,c);
                }else{
                    S2=CD(r,c);
                }
            }
        }
    }
    unordered_set<CD,CD::Hash> visitedReps;
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if(lake[r][c]!='X' && (unions[r][c].row==-1?1:visitedReps.find(findRep(CD(r,c)))==visitedReps.end())){
                CD cur(r,c);
                vector<vector<bool>> visited(MAX,vector<bool>(MAX));
                DFS(visited,cur,cur);
                visitedReps.insert(cur);
                reps.push_back(cur);
            }
        }
    }
    int days = 0;
    while(!(findRep(S1)==findRep(S2))){
        days++;
        //merge
        unordered_map<CD,CD,CD::Hash> repMap; 
        for(list<CD>::iterator it = reps.begin(); it != reps.end(); ++it){
            CD &rep = *it;
            vector<CD> &connections = unionConnections[rep.row][rep.col];
            vector<CD> newConnections;
            unordered_set<CD,CD::Hash> added;
            for(int i = 0; i < connections.size(); ++i){
                lake[connections[i].row][connections[i].col]='.';
                if(repMap.find(connections[i])==repMap.end()){
                    //new - unclaimed block
                    repMap[connections[i]]=rep;
                    unions[connections[i].row][connections[i].col]=rep;
                }else{
                    //duplicate - two unions trying to take over the same block; merge unions
                    CD &curRep = repMap[connections[i]];
                    curRep = findRep(curRep);
                    unions[curRep.row][curRep.col]=rep;
                }
                //merging with neighbors that are claimed
                for(int j = 0; j < 4; ++j){
                    CD nxt(connections[i].row+dirR[j],connections[i].col+dirC[j]);
                    if(!(nxt.row < R && nxt.row >= 0 && nxt.col < C && nxt.col >=0)){continue;}
                    if(repMap.find(nxt)!=repMap.end()){
                        CD &neighborRep = repMap[nxt];
                        neighborRep = findRep(neighborRep);
                        unions[neighborRep.row][neighborRep.col]=rep;
                    }
                    if(lake[nxt.row][nxt.col]=='X' && added.find(nxt)==added.end()){
                        newConnections.push_back(nxt);
                        added.insert(nxt);
                    }
                }
            }
            unionConnections[rep.row][rep.col]=newConnections;
        }
        for(list<CD>::iterator it = reps.begin(); it != reps.end(); ++it){
            CD &rep = *it;
            if(!(findRep(rep)==rep)){
                it=reps.erase(it);
                it--;
                continue;
            }
            vector<CD> &connections = unionConnections[rep.row][rep.col];
            vector<CD> prunedConnections;
            for(int i = 0; i < connections.size(); ++i){
                if(lake[connections[i].row][connections[i].col]=='X'){
                    prunedConnections.push_back(connections[i]);
                }
            }
            connections=prunedConnections;
        }
    }
    std::cout<<days<<"\n";
}