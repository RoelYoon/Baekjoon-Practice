#include <iostream>
#include <vector>
#define ll long long
using namespace std;
const int M = 1000;
int n;
void multiply(int m1[][5], int m2[][5], int m3[][5]){
    int temp[5][5]{};
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            for(int k = 0; k < n; ++k){
                temp[r][c] = (temp[r][c]+(m1[r][k] * m2[k][c])%M)%M;
            }
        }
    }
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            m3[r][c] = temp[r][c];
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll b;
    int mat[5][5]{};
    cin>>n>>b;
    int p2[40][5][5];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin>>p2[0][i][j];
        }
        mat[i][i] = 1;
    }
    for(int p = 1; p < 40; ++p){
        multiply(p2[p-1], p2[p-1], p2[p]);
    }
    int p = 0;
    while(b){
        if(b&1){
            multiply(mat, p2[p], mat);
        }
        ++p;
        b>>=1;
    }
    for(int r = 0; r < n; ++r){
        for(int c = 0; c < n; ++c){
            cout<<mat[r][c]<<(c==n-1?"\n":" ");
        }
    }
}