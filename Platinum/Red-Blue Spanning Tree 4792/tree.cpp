#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Edge{
    bool blue;
    int u;
    int v;
    Edge(){};
    Edge(bool b, int u, int v):blue(b),u(u),v(v){}
};
class UnionFind{
    int n;
    vector<int> reps;
    vector<int> ranks;
    public:
    UnionFind(int n):n(n), reps(n),ranks(n,0){
        for(int i = 0; i < n; ++i)
            reps[i]=i;
    }
    int find(int head){
        if(reps[head]==head)
            return head;
        return reps[head]=find(reps[head]);
    }
    void merge(int a, int b){
        a = find(a);
        b = find(b);
        if(ranks[a] < ranks[b]){
            reps[a] = b;
        }else if(ranks[b] < ranks[a]){
            reps[b] = a;
        }else{
            reps[a] = b;
            ++ranks[b];
        }
    }
    void clear(){
        for(int i = 0; i < n; ++i){
            reps[i]=i;
            ranks[i]=0;
        }
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        int n,m,k; cin>>n>>m>>k;
        if(n==0 && m==0 && k==0) break;
        vector<Edge> edges(m);
        UnionFind redUnions(n);
        UnionFind mstUnions(n);
        for(int i = 0; i < m; ++i){
            char c;
            int a, b;
            cin>>c>>a>>b;
            edges[i].blue = c=='B';
            edges[i].u = a-1;
            edges[i].v = b-1;
            if(!edges[i].blue){
                redUnions.merge(edges[i].u, edges[i].v);
            }
        }
        sort(edges.begin(),edges.end(),[](Edge &a, Edge &b){return a.blue > b.blue;});
        int minBlueEdges = 0, maxBlueEdges=0;
        for(int i = 0; i < m && edges[i].blue; ++i){
            int a = redUnions.find(edges[i].u);
            int b = redUnions.find(edges[i].v);
            if(mstUnions.find(a) != mstUnions.find(b)){
                ++minBlueEdges;
                mstUnions.merge(a,b);
            }
        }
        mstUnions.clear();
        for(int i = 0; i < m; ++i){
            int a = edges[i].u;
            int b = edges[i].v;
            if(mstUnions.find(a) != mstUnions.find(b)){
                maxBlueEdges+=edges[i].blue;
                mstUnions.merge(a,b);
            }
        }
        cout<<(k >= minBlueEdges && k <= maxBlueEdges ? 1 : 0)<<"\n";
    }
}
/*
9 12 4
R 9 3
R 1 2
R 5 6
R 6 8
R 5 8
B 3 7
B 4 7
B 9 1
B 4 5
B 1 5
B 2 6
B 9 4
0 0 0

5 6 1
B 1 2
B 2 3
B 3 4
B 4 5
R 1 3
R 2 5
0 0 0
*/