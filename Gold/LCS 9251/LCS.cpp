#include <iostream>
using namespace std;
int DP[1000][1000]{};
string a,b;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>a>>b;
    int n = a.size(),m=b.size();
    DP[0][0]=a[0]==b[0];
    for(int i = 1; i < n; ++i)
        DP[i][0]=DP[i-1][0]||a[i]==b[0];
    for(int j = 1; j < m; ++j)
        DP[0][j]=DP[0][j-1]||a[0]==b[j];
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < m; ++j){
            if(a[i]==b[j])
                DP[i][j]=DP[i-1][j-1]+1;
            else
                DP[i][j]=max(DP[i-1][j],DP[i][j-1]);
        }
    }
    cout<<DP[n-1][m-1]<<"\n";
}