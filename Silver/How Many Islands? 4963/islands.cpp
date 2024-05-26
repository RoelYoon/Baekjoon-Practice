#include <iostream>
#include <vector>
using namespace std;
int dirRow[8]{-1,1,0,0,-1,1,-1,1};
int dirCol[8]{0,0,-1,1,-1,-1,1,1};
void DFS(vector<vector<int>> &mat, vector<vector<int>> &visited, int r, int c){
    if(visited[r][c])
        return;
    visited[r][c] = true;
    for(int i = 0; i < 8; i++)
        if(mat[r][c]==1 && r+dirRow[i]>=0 && r+dirRow[i]<mat.size() && c+dirCol[i]>=0 && c+dirCol[i]<mat[0].size())
            DFS(mat,visited,r+dirRow[i],c+dirCol[i]);
}
int main(){
    int n,m;
    while(1){
        cin>>m>>n;
        if(n==0 && m==0){break;}
        vector<vector<int>> mat(n,vector<int>(m));
        vector<vector<int>> visited(n,vector<int>(m));
        for(int r = 0; r < n; r++)
            for(int c = 0; c < m; c++)
                cin>>mat[r][c];
        int count = 0;
        for(int r = 0; r < n; r++){
            for(int c = 0; c < m; c++){
                if(mat[r][c]==1 && !visited[r][c]){count++;}
                DFS(mat,visited,r,c);
            }
        }
        cout<<count<<"\n";
    }
}