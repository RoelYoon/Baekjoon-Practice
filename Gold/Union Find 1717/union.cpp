#include <iostream>
#include <vector>
using namespace std;
int find(vector<int> &unions, int head){
    if(unions[head]==head){return head;}
    int ans = find(unions,unions[head]);
    unions[head] = ans;
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m; 
    cin>>n>>m; 
    vector<int> unions(n+1);
    for(int i = 0; i < n+1; i++)
        unions[i]=i;
    for(int i = 0; i < m; i++){
        int op, a, b; 
        cin>>op>>a>>b; 
        switch(op){
            case 0:
                //union
                unions[find(unions,b)]=find(unions,a);
                break;
            case 1: 
                //find
                cout<<(find(unions,a) == find(unions,b) ? "YES\n" : "NO\n"); 
                break;
        }
    }
}