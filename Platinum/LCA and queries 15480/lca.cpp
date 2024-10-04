#include <iostream>
#include <vector>
#include <cmath>
#define MAX 100005
using namespace std;
int level[MAX];
int parent[MAX][18]{};
vector<vector<int>> graph;
int LOG;
int LCA(int a, int b){
    //make sure a is lower than b
    if(level[a]<level[b]){
        int t = a;
        a = b;
        b = t;
    }
    int d = level[a]-level[b];
    for(int i = LOG; i >= 0; --i){
        if(d & (1<<i)){
            a=parent[a][i];
        }
    }
    if(a==b){return a;}
    //nodes are at equal levels
    for(int i = LOG; i>=0; --i){
        if(parent[a][i]!=parent[b][i]){
            a=parent[a][i];
            b=parent[b][i];
        }
    }
    return parent[a][0];
}
void LCA_DFS(int head, int depth){
    if(level[head]!=-1) return;
    level[head]=depth;
    for(int i = 0; i < graph[head].size(); ++i){
        if(level[graph[head][i]]!=-1) continue;
        parent[graph[head][i]][0]=head;
        for(int j = 1; j <= LOG; ++j){
            parent[graph[head][i]][j]=parent[parent[graph[head][i]][j-1]][j-1];
        }
        LCA_DFS(graph[head][i],depth+1);
    }
}
//1 assumed as root
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n;
    for(int i = 0; i < n; ++i)
        level[i]=-1;
    graph.resize(n);
    LOG=ceil(log2(n));
    for(int i = 0; i < n-1; ++i){
        int a,b; cin>>a>>b; --a,--b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 0; i <= LOG; ++i)
        parent[0][i]=0; //initialize root
    LCA_DFS(0,0);
    cin>>q;
    for(int i = 0; i < q; ++i){
        int r,a,b,l1,l2,l3;
        cin>>r>>a>>b;--r,--a,--b;
        l1=LCA(a,b)+1;
        l2=LCA(r,a)+1;
        l3=LCA(r,b)+1;
        if(l1==l2){
            cout<<l3<<"\n";
        }else if(l1==l3){
            cout<<l2<<"\n";
        }else{
            cout<<l1<<"\n";
        }
    }
}