#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define pt complex<int>
#define R real()
#define C imag()
using namespace std;
const int dirR[4]{0,1,0,-1},dirC[4]{1,0,-1,0};
int RR,CC,files;
string keys;
void DFS(char map[100][100],bool visited[100][100],bool keyFound[125],vector<vector<pt>> &doors,pt head){
    if(!(head.R>=0 && head.C>=0 && head.R<RR && head.C<CC) || visited[head.R][head.C] || map[head.R][head.C]=='*') return;
    visited[head.R][head.C]=1;
    char c = map[head.R][head.C];
    files+=c=='$';
    if(c<97 && !keyFound[c] && c!='$'){
        visited[head.R][head.C]=0;
        doors[c].push_back(head);
        return;
    }
    if(c>96 && !keyFound[c-32]){
        keys.push_back(c);
        keyFound[c-32]=1;
        if(!doors[c-32].empty()){
            for(int i = 0; i < doors[c-32].size(); ++i)
                DFS(map,visited,keyFound,doors,doors[c-32][i]);
        }
    }
    for(int i = 0; i < 4; ++i){
        DFS(map,visited,keyFound,doors,pt(head.R+dirR[i],head.C+dirC[i]));
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        cin>>RR>>CC;
        char map[100][100];
        bool visited[100][100]{};
        bool keyFound[125]{}; keyFound['.']=1;
        vector<vector<pt>> doors(125);
        files=0;
        for(int r = 0; r < RR; ++r){
            for(int c = 0; c < CC; ++c){
                cin>>map[r][c];
            }
        }
        cin>>keys;
        if(keys!="0")
            for(int i = 0; i < keys.size(); ++i)
                keyFound[keys[i]-32]=1;
        for(int r=0; r < RR; ++r){
            DFS(map,visited,keyFound,doors,pt(r,0));
            DFS(map,visited,keyFound,doors,pt(r,CC-1));
        }
        for(int c=0; c < CC; ++c){
            DFS(map,visited,keyFound,doors,pt(0,c));
            DFS(map,visited,keyFound,doors,pt(RR-1,c));
        }
        for(int i = 0; i < keys.size(); ++i){
            for(int j = 0; j < doors[keys[i]-32].size(); ++j){
                DFS(map,visited,keyFound,doors,doors[keys[i]-32][j]);
            }
        }
        cout<<files<<"\n";
    }
}