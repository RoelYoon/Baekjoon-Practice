#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;
int n;
int MX;
int dirR[4]{0,1,0,-1};
int dirC[4]{1,0,-1,0};
int move(int grid[20][20], int nxtGrid[20][20], bool &mergedV, bool &change, int dir) {
    int mx = 0;
    for(int r=0;r<n; ++r){
        for(int c=0;c<n;++c){
            nxtGrid[r][c] = grid[r][c];
            mx = max(mx, grid[r][c]);
        }
    }
    int line[20], out[20];
    for(int i = 0; i < n; ++i) {
        int len = 0;
        for(int j = 0; j < n; ++j) {
            int val = (dir==0||dir==2) ? nxtGrid[i][j] : nxtGrid[j][i];
            int idx = (dir==0||dir==3) ? n-1-j : j;
            int v = (dir==0||dir==2) ? nxtGrid[i][idx] : nxtGrid[idx][i];
            if(v) line[len++] = v;
        }
        int olen = 0;
        bool merged = 0;
        memset(out, 0, sizeof(out));
        for(int j = 0; j < len; ++j) {
            if(!merged && olen > 0 && out[olen-1] == line[j]) {
                out[olen-1] *= 2;
                mx = max(mx, out[olen-1]);
                merged = 1;
                mergedV = 1;
            } else {
                out[olen++] = line[j];
                merged = 0;
            }
        }
        for(int j = 0; j < n; ++j) {
            int val = (j < olen) ? out[j] : 0;
            int idx = (dir==0||dir==3) ? n-1-j : j;
            int &cell = (dir==0||dir==2) ? nxtGrid[i][idx] : nxtGrid[idx][i];
            if(cell != val) { cell = val; change = true; }
        }
    }
    return mx;
}
/*
int move(int grid[20][20], int nxtGrid[20][20], bool &merged, bool &change, int dir){
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
                    merged = 1;
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
                    merged = 1;
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
                    merged = 1;
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
                    merged = 1;
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
}*/
unordered_map<size_t,int> visited;
size_t hashGrid(int g[20][20]) {
    size_t h = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            h = h * 1000003ULL + g[i][j];
    return h;
}
int nxtGrid[10][20][20];
int gAns = 0;
int maxVal(int grid[20][20], int m, int nm, int d){
    if(d==10 || nm>2) return 0;
    size_t h = hashGrid(grid);
    unordered_map<size_t,int>::iterator it = visited.find(h);
    if(it != visited.end() && it->second <= d) return 0;
    visited[h] = d;
    int ans = 0;
    for(int i = 0; i < 4; ++i){
        if(i==m) continue;
        bool merged = 0;
        bool change = 0;
        ans = max(ans, move(grid, nxtGrid[d], merged, change, i));
        gAns=max(gAns,ans);
        if(!change) continue;
        if(ans==MX || (ans << (10-d)) <= gAns) return ans;
        ans = max(ans, maxVal(nxtGrid[d], merged?-1:(i+2)%4, merged?0:nm+1, d+1)); 
        gAns=max(gAns,ans);
        if(ans==MX || (ans << (10-d)) <= gAns) return ans;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    MX = 0;
    int grid[20][20];
    for(int r = 0; r < n; ++r){
        for(int c = 0; c< n; ++c){
            cin>>grid[r][c];
            MX+=grid[r][c];
        }
    }
    cout<<maxVal(grid,-1,0,0)<<"\n";
 }