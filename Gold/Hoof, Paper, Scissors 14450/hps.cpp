#include <iostream>
#include <vector>
using namespace std;
int n,k;
vector<int> gs;
inline bool wins(int B, int FJ){
    return B==0 && FJ==2 || B==1 && FJ==0 || B==2 && FJ==1;
}
int DP[3][21][(int)1e5]{};
int wins(int move,int changes,int turn){
    if(turn==n) return 0;
    if(changes>k) return 0;
    if(DP[move][changes][turn]>0) return DP[move][changes][turn];
    return DP[move][changes][turn]=max(wins(move,changes,turn+1),max(wins((move+1)%3,changes+1,turn+1),wins((move+2)%3,changes+1,turn+1)))+wins(move,gs[turn]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    gs.resize(n);
    for(int i = 0; i < n; ++i){
        char g; cin>>g;
        switch(g){
            case 'H':
                gs[i]=0;
                break;
            case 'P':
                gs[i]=1;
                break;
            case 'S':
                gs[i]=2;
                break;
        }
    }
    cout<<max(wins(0,0,0),max(wins(1,0,0),wins(2,0,0)));
}