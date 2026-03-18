#include <iostream>
#include <vector>
using namespace std;
struct Edge{
    int u,v,w;
    Edge(){}
    Edge(int u, int v, int w):u(u),v(v),w(w){}
};
int DP[10000]{};
int maxLength(vector<Edge> &edges, vector<vector<int>> &graph, int head){
    if(DP[head]) return DP[head];
    int mxL = 0;
    for(int i = 0; i < graph[head].size(); ++i){
        Edge &edge = edges[graph[head][i]];
        mxL = max(mxL, maxLength(edges,graph,edge.v)+edge.w);
    }
    return DP[head]=mxL;
}
int findDiameter(vector<Edge> &edges, vector<vector<int>> &graph, int head){
    int mxs[2]{};
    int mxD = 0;
    for(int i = 0; i < graph[head].size(); ++i){
        Edge &edge = edges[graph[head][i]];
        int l = maxLength(edges, graph, edge.v)+edge.w;
        if(l>mxs[0]){
            mxs[0] = l;
            if(mxs[0]>mxs[1]){
                int t = mxs[0];
                mxs[0] = mxs[1];
                mxs[1] = t;
            }
        }
        mxD = max(mxD, findDiameter(edges, graph, edge.v));
    }
    mxD = max(mxD, mxs[0]+mxs[1]);
    return mxD;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Edge> edges;
    vector<vector<int>> graph(n);
    vector<bool> isRoot(n,1);
    for(int i = 0; i < n-1; ++i){
        int p,v,w; cin>>p>>v>>w;
        --p,--v;
        edges.emplace_back(p,v,w);
        graph[p].push_back(edges.size()-1);
        isRoot[v]=0;
    }
    int root = -1;
    for(int i = 0; i < n; ++i){
        if(isRoot[i]){
            cout<<findDiameter(edges, graph, i)<<"\n";
            break;
        }
    }
}