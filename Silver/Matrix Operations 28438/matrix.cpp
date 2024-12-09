#include <iostream>
#include <vector>
#define ll long long
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R,C,Q; cin>>R>>C>>Q;
    vector<vector<ll>> mat(R,vector<ll>(C));
    vector<ll> dr(R),dc(C);
    for(int i = 0; i < Q; ++i){
        int t; cin>>t;
        if(t==1){
            int r,v; cin>>r>>v; --r;
            dr[r]+=v;
        }else{
            int c,v; cin>>c>>v; --c;
            dc[c]+=v;
        }
    }
    for(int r = 0 ; r < R; ++r)
        for(int c = 0 ; c < C; ++c)
            mat[r][c]+=dr[r];
    for(int c= 0 ; c < C; ++c)
        for(int r = 0; r < R; ++r)
            mat[r][c]+=dc[c];
    for(int r= 0; r < R; ++r){
        for(int c =0 ; c< C; ++c)
            cout<<mat[r][c]<<" ";
        cout<<"\n";
    }
}