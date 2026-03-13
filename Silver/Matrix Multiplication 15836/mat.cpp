#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t=1;
    while(1){
        int R1,C1,R2,C2; cin>>R1>>C1>>R2>>C2;
        if(R1+C1+R2+C2==0) break;
        cout<<"Case #"<<t++<<":\n";
        int mat1[20][20],mat2[20][20];
        for(int r = 0; r < R1; ++r){
            for(int c = 0; c < C1; ++c){
                cin>>mat1[r][c];
            }
        }
        for(int r = 0; r < R2; ++r){
            for(int c = 0; c < C2; ++c){
                cin>>mat2[r][c];
            }
        }
        if(C1!=R2){
            cout<<"undefined\n";
            continue;
        }
        int mat3[20][20]{};
        for(int r = 0; r < R1; ++r){
            for(int c = 0; c < C2; ++c){
                for(int k = 0; k < R2; ++k){
                    mat3[r][c]+=mat1[r][k]*mat2[k][c];
                }
            }
        }
        for(int r = 0; r < R1; ++r){
            cout<<"| ";
            for(int c = 0; c < C2; ++c){
                cout<<mat3[r][c]<<" ";
            }
            cout<<"|\n";
        }
    }
}