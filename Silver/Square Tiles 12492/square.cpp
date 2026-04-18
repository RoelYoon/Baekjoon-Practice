#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    for(int t = 0; t < T; ++t){
        int R,C; cin>>R>>C;
        vector<string> grid(R);
        for(int r = 0; r < R; ++r){
            cin>>grid[r];
        }
        bool imp = 0;
        for(int r = 0; r < R; ++r){
            for(int c = 0; c < C; ++c){
                if(grid[r][c] == '#'){
                    grid[r][c] = '/';
                    if((c+1) >= C || grid[r][c+1]!='#'){
                        imp = 1;
                        break;               
                    }
                    grid[r][c+1] = '\\';
                    if((r+1) >= R || grid[r+1][c]!='#' || grid[r+1][c+1]!='#'){
                        imp = 1;
                        break;               
                    }
                    grid[r+1][c] = '\\';
                    grid[r+1][c+1] = '/';
                }
            }
            if(imp) break;
        }
        cout<<"Case #"<<t+1<<":\n";
        if(imp){
            cout<<"Impossible\n";
            continue;
        }
        for(int r = 0;r < R; ++r){
            cout<<grid[r]<<"\n";
        }
    }
}