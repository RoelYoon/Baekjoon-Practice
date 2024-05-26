#include <iostream>
#include <vector>
#include <list>
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
};
int R,C;
const int dirR[4]{-1,0,1,0};
const int dirC[4]{0,1,0,-1};
CD findRep(vector<vector<CD>> &unions, CD head){
    if(unions[head.row][head.col]==head)
        return head;
    CD rep = findRep(unions,unions[head.row][head.col]);
    unions[head.row][head.col]=rep;
    return rep;
}
void DFS(char lake[MAX][MAX],vector<vector<bool>> &visited, vector<vector<CD>> &unions, vector<vector<list<CD>>> &unionConnections,CD &originRep, CD head){
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
                DFS(lake,visited,unions,unionConnections,originRep,nxt);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("in","r",stdin);
    cin>>R>>C;
    char lake[MAX][MAX];
    vector<vector<CD>> unions(MAX,vector<CD>(MAX));
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
    bool visitedReps[MAX][MAX]{};
    vector<vector<list<CD>>> unionConnections(MAX,vector<list<CD>>(MAX));
    list<CD> reps; 
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            if(lake[r][c]!='X' && (unions[r][c].row==-1?1:visitedReps[r][c])){
                CD cur(r,c);
                vector<vector<bool>> visited(MAX,vector<bool>(MAX));
                DFS(lake,visited,unions,unionConnections,cur,cur);
                visitedReps[r][c]=1;
                reps.push_back(cur);
            }
        }
    }
    int days = 0;
    while(!(findRep(unions,S1)==findRep(unions,S2))){
        days++;
        //merge
        vector<vector<CD>> repMap(MAX,vector<CD>(MAX));
        for(list<CD>::iterator it = reps.begin(); it != reps.end(); it++){
            CD &rep = *it;
            list<CD> &connections = unionConnections[rep.row][rep.col];
            CD end = connections.back();
            bool added[MAX][MAX]{};
            for(list<CD>::iterator cIt = connections.begin(); cIt!=connections.end(); cIt++){
                lake[cIt->row][cIt->col]='.';
                if(repMap[cIt->row][cIt->col].row==-1){
                    //new - unclaimed block
                    repMap[cIt->row][cIt->col]=rep;
                    unions[cIt->row][cIt->col]=rep;
                }else{
                    //duplicate - two unions trying to take over the same block; merge unions
                    CD &curRep = repMap[cIt->row][cIt->col];
                    curRep = findRep(unions,curRep);
                    unions[curRep.row][curRep.col]=rep;
                }
                //merging with neighbors that are claimed
                for(int j = 0; j < 4; j++){
                    CD nxt(cIt->row+dirR[j],cIt->col+dirC[j]);
                    if(!(nxt.row < R && nxt.row >= 0 && nxt.col < C && nxt.col >=0)){continue;}
                    if(repMap[nxt.row][nxt.col].row!=-1){
                        CD &neighborRep = repMap[nxt.row][nxt.col];
                        neighborRep = findRep(unions,neighborRep);
                        unions[neighborRep.row][neighborRep.col]=rep;
                    }
                    if(lake[nxt.row][nxt.col]=='X'){
                        if(!added[nxt.row][nxt.col]){
                            connections.push_back(nxt);
                            added[nxt.row][nxt.col]=1;
                        }
                    }
                }
                if(*cIt==end){
                    cIt=connections.erase(cIt);
                    cIt--;
                    break;
                }
                cIt=connections.erase(cIt);
                cIt--;
            }
        }
        for(list<CD>::iterator it = reps.begin(); it != reps.end(); it++){
            CD &rep = *it;
            if(!(findRep(unions,rep)==rep)){
                CD realRep = findRep(unions,rep);
                unionConnections[realRep.row][realRep.col].insert(unionConnections[realRep.row][realRep.col].begin(),unionConnections[rep.row][rep.col].begin(),unionConnections[rep.row][rep.col].end());
                it=reps.erase(it);
                it--;
                continue;
            }
            list<CD> &connections = unionConnections[rep.row][rep.col];
            for(list<CD>::iterator cIt = connections.begin(); cIt!=connections.end(); cIt++){
                if(lake[cIt->row][cIt->col]!='X'){
                    cIt=connections.erase(cIt);
                    cIt--;
                }
            }
        }
    }
    std::cout<<days<<"\n";
}