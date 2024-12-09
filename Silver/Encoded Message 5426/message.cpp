#include <iostream>
#include <cmath>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        string s; cin>>s;
        int n = sqrt(s.size());
        int si = 0;
        char board[100][100];
        for(int r = 0; r < n; ++r)
            for(int c = 0; c < n; ++c)
                board[r][c]=s[si++];
        string message="";
        for(int c = n-1; c>=0; --c)
            for(int r = 0; r < n; ++r)
                message+=board[r][c];
        cout<<message<<"\n";
    }
}