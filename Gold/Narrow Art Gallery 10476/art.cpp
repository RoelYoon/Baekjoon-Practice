#include <iostream>
using namespace std;
int n,k;
int minBlock=1000000000;
struct RoomPair{
    int x;
    int y;
    RoomPair(){}
};
RoomPair gallery[205];
int mem[205][3][205]{};
void DFS(int picked, int val,int state,int level){
    if(picked==k){
        minBlock = min(minBlock,val);
        return;
    }
    if(level == n || mem[picked][state][level] <= val) return;
    mem[picked][state][level]=val;
    if(state==0 || state==2){//x picked
        DFS(picked+1,val+gallery[level].x,0,level+1);
    }
    if(state==1 || state==2){//y picked
        DFS(picked+1,val+gallery[level].y,1,level+1);
    }
    DFS(picked,val,2,level+1);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k;
    int totalVal = 0;
    for(int i = 0; i < n+1; i++){
        cin>>gallery[i].x>>gallery[i].y;
        totalVal+=gallery[i].x + gallery[i].y;
    }
    for(int i = 0; i < 205; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 205; k++){
                mem[i][j][k]=1000000000;
            }
        }
    }
    DFS(0,0,2,0);
    cout<<totalVal-minBlock<<"\n";
}