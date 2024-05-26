#include <iostream>
#include <vector>
using namespace std;
int main(){
    freopen("in","w",stdout);
    int n = 1500;
    vector<vector<char>> mat(n,vector<char>(n));
    cout<<n<<" "<<n<<"\n";
    for(int r = 0; r < 2; r++){
        for(int c = 0; c < n; c++){
            mat[r][c] = '.';
        }
    }
    for(int r = 2; r < n-2; r++){
        for(int c = 0; c < n; c++){
            mat[r][c] = 'X';
        }
    }
    for(int r = n-2; r < n; r++){
        for(int c = 0; c < n; c++){
            mat[r][c] = '.';
        }
    }
    mat[0][0]='L'; mat[n-1][n-1]='L';
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
           cout<<mat[r][c];
        }cout<<"\n";
    }cout<<endl;
    return 0;
}