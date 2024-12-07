#include <iostream>
#include <vector>
using namespace std;
int MXV[101][100001]{}; // maximum value at index i with cap c = MXV[i][c]
struct Item{
    int w,v;
    Item(){}
    Item(int w, int v):w(w),v(v){}
};
vector<Item> items;
int mxV(int i, int c){
    if(i<0 || c<=0) return 0;
    if(MXV[i][c]!=-1) return MXV[i][c];
    return MXV[i][c]=max(mxV(i-1,c),(items[i].w<=c?mxV(i-1,c-items[i].w)+items[i].v:0));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>>n>>k;
    for(int i = 0; i < 101; ++i)
        for(int j = 0; j < 100001; ++j)
            MXV[i][j]=-1;
    items.resize(n);
    for(int i = 0; i < n; ++i)
        cin>>items[i].w>>items[i].v;
    cout<<mxV(n,k)<<"\n";
}