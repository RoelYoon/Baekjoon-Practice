#include <iostream>
#include <random>
#include <time.h>
using namespace std;
int n;
int MX;
int dirR[4]{0,1,0,-1};
int dirC[4]{1,0,-1,0};
int move(int grid[20][20], int nxtGrid[20][20], bool &change, int dir){
    int mx = 0;
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            nxtGrid[r][c] = grid[r][c];
            mx = max(mx, grid[r][c]);
        }
    }
    if(dir==0){
        // c ->
        for(int r = 0; r < n; ++r){
            for(int c = n-1; c >= 0; --c){
                int nc = c+1;
                while(nc<n && !nxtGrid[r][nc]){
                    ++nc;
                }
                --nc;
                nxtGrid[r][nc] = nxtGrid[r][c];
                if(nc!=c){
                    nxtGrid[r][c] = 0;
                    change = 1;
                }
            }
        }
        for(int r = 0; r < n; ++r){
            for(int c = n-1; c >= 1; --c){
                if(nxtGrid[r][c-1] == nxtGrid[r][c]){
                    nxtGrid[r][c]*=2;
                    nxtGrid[r][c-1]=0;
                    mx = max(mx, nxtGrid[r][c]);
                    change = 1;
                }
            }
        }
        for(int r = 0; r < n; ++r){
            for(int c = n-1; c >= 0; --c){
                int nc = c+1;
                while(nc<n && !nxtGrid[r][nc]){
                    ++nc;
                }
                --nc;
                nxtGrid[r][nc] = nxtGrid[r][c];
                if(nc!=c){
                    nxtGrid[r][c] = 0;
                    change = 1;
                }
            }
        }
    }else if(dir==1){
        // r ->
        for(int c = 0; c < n; ++c){
            for(int r = n-1; r >= 0; --r){
                int nr = r+1;
                while(nr<n && !nxtGrid[nr][c]){
                    ++nr;
                }
                --nr;
                nxtGrid[nr][c] = nxtGrid[r][c];
                if(nr!=r){
                    nxtGrid[r][c] = 0; 
                    change = 1;
                }
            }
        }
        for(int c = 0; c < n; ++c){
            for(int r = n-1; r >= 1; --r){
                if(nxtGrid[r-1][c] == nxtGrid[r][c]){
                    nxtGrid[r][c]*=2;
                    nxtGrid[r-1][c]=0;
                    mx = max(mx, nxtGrid[r][c]);
                    change = 1;
                }
            }
        }
        for(int c = 0; c < n; ++c){
            for(int r = n-1; r >= 0; --r){
                int nr = r+1;
                while(nr<n && !nxtGrid[nr][c]){
                    ++nr;
                }
                --nr;
                nxtGrid[nr][c] = nxtGrid[r][c];
                if(nr!=r){
                    nxtGrid[r][c] = 0; 
                    change = 1;
                }
            }
        }
    }else if(dir==2){
        // c <-
        for(int r = 0; r < n; ++r){ 
            for(int c = 0; c < n; ++c){
                int nc = c-1;
                while(nc>=0 && !nxtGrid[r][nc]){
                    --nc;
                }
                ++nc;
                nxtGrid[r][nc] = nxtGrid[r][c];
                if(nc!=c){
                    nxtGrid[r][c] = 0;
                    change = 1;
                }
            }
        }
        for(int r = 0; r < n; ++r){ 
            for(int c = 0; c < n-1; ++c){
                if(nxtGrid[r][c+1] == nxtGrid[r][c]){
                    nxtGrid[r][c]*=2;
                    nxtGrid[r][c+1]=0;
                    mx = max(mx, nxtGrid[r][c]);
                    change = 1;
                }
            }
        }
        for(int r = 0; r < n; ++r){ 
            for(int c = 0; c < n; ++c){
                int nc = c-1;
                while(nc>=0 && !nxtGrid[r][nc]){
                    --nc;
                }
                ++nc;
                nxtGrid[r][nc] = nxtGrid[r][c];
                if(nc!=c){
                    nxtGrid[r][c] = 0;
                    change = 1;
                }
            }
        }
    }else{
        // r <-
        for(int c = 0; c < n; ++c){
            for(int r = 0; r < n; ++r){
                int nr = r-1;
                while(nr>=0 && !nxtGrid[nr][c]){
                    --nr;
                }
                ++nr;
                nxtGrid[nr][c] = nxtGrid[r][c];
                if(nr!=r){
                    nxtGrid[r][c] = 0;
                    change = 1;
                }
            }
        }
        for(int c = 0; c < n; ++c){
            for(int r = 0; r < n-1; ++r){
                if(nxtGrid[r+1][c] == nxtGrid[r][c]){
                    nxtGrid[r][c]*=2;
                    nxtGrid[r+1][c]=0;
                    mx = max(mx, nxtGrid[r][c]);
                    change = 1;
                }
            }
        }
        for(int c = 0; c < n; ++c){
            for(int r = 0; r < n; ++r){
                int nr = r-1;
                while(nr>=0 && !nxtGrid[nr][c]){
                    --nr;
                }
                ++nr;
                nxtGrid[nr][c] = nxtGrid[r][c];
                if(nr!=r){
                    nxtGrid[r][c] = 0;
                    change = 1;
                }
            }
        }
    }
    return mx;
}
int maxVal(int grid[20][20], int m, int d){
    if(d==5) return 0;
    int nxtGrid[20][20];
    int ans = 0;
    int j = rand()%4;
    for(int i = 0; i < 4; ++i){
        if(j==m) continue;
        bool change = 0;
        ans = max(ans, move(grid, nxtGrid, change, j));
        if(ans==MX) return ans;
        ans = max(ans, maxVal(nxtGrid, change?-1:j, d+1)); 
        if(ans==MX) return ans;
        j = (j+1)%4;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    cin>>n;
    MX = 0;
    int grid[20][20];
    for(int r = 0; r < n; ++r){
        for(int c = 0; c< n; ++c){
            cin>>grid[r][c];
            MX+=grid[r][c];
        }
    }
    cout<<maxVal(grid,-1,0)<<"\n";
 }