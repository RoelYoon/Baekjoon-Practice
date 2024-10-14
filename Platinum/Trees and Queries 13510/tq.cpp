#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
struct Edge{
    int u;
    int v;
    int c;
    Edge(){}
    Edge(int u, int v):u(u),v(v),c(-1){}
    Edge(int u, int v, int c):u(u),v(v),c(c){}
    bool operator==(const Edge &e) const {
        return u==e.u && v==e.v;
    }
    struct Hash{
        size_t operator()(const Edge &a) const {
            return (hash<int>{}(a.u)*31)^hash<int>{}(a.v);
        }
    };
};
struct LCA_Node{
    int id;
    int val;
    LCA_Node(){}
    LCA_Node(int i, int v):id(i),val(v){}
    bool operator<(const LCA_Node &other) const {
        return val<other.val;
    }
    bool operator>(const LCA_Node &other) const {
        return val>other.val;
    }
};
enum Type{
    LCA_TREE,
    HLD_TREE
};
template <Type T>
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    #define LCA_T(t) template <Type U> \
    typename enable_if<U==LCA_TREE,t>::type
    #define HLD_T(t) template <Type U> \
    typename enable_if<U==HLD_TREE,t>::type
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<conditional_t<T==LCA_TREE,LCA_Node,int>> st;
    LCA_T(LCA_Node) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return LCA_Node(-1,1e9);
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return min(query<LCA_TREE>(LC(p),L,mid,QL,QR),query<LCA_TREE>(RC(p),mid+1,R,QL,QR));
    }
    HLD_T(int) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return max(query<HLD_TREE>(LC(p),L,mid,QL,QR),query<HLD_TREE>(RC(p),mid+1,R,QL,QR));
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]=u;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=max(st[LC(p)],st[RC(p)]);
    }
    LCA_T(void) build(int p, int L, int R, vector<int>&data, vector<int> &key){
        if(L==R){
            st[p]=LCA_Node(key[L],data[key[L]]);
            return;
        }
        int mid = (L+R)/2;
        build<LCA_TREE>(LC(p),L,mid,data,key);
        build<LCA_TREE>(RC(p),mid+1,R,data,key);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    HLD_T(void) build(int p, int L, int R, vector<Edge> &edges, vector<int> &key){
        if(L==R){
            st[p]=edges[key[L]].c;
            return;
        }
        int mid = (L+R)/2;
        build<HLD_TREE>(LC(p),L,mid,edges,key);
        build<HLD_TREE>(RC(p),mid+1,R,edges,key);
        st[p]=max(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(){}
    template <Type U=T>
    SegmentTree(int n, vector<int>&data, vector<int> &key, typename enable_if<U==LCA_TREE>::type*a=0):n(n),st(4*n){build<LCA_TREE>(0,0,n-1,data,key);}
    template <Type U=T>
    SegmentTree(int n, vector<Edge> &edges, vector<int> &key, typename enable_if<U==HLD_TREE>::type*a=0):n(n),st(4*n){build<HLD_TREE>(0,0,n-1,edges,key);}
    LCA_T(int) query(int L, int R){
        return query<LCA_TREE>(0,0,n-1,L,R).id;
    }
    HLD_T(int) query(int L, int R){
        return query<HLD_TREE>(0,0,n-1,L,R);
    }
    void update(int P, int U){
        return update(0,0,n-1,P,P,U);
    }
};
vector<vector<int>> graph;
vector<Edge> edges;
vector<bool> visited;
vector<int> level;
vector<int> parent;
vector<int> et;
vector<int> start;
vector<int> heavyChild;
vector<int> reps;
vector<int> rep2Chain;
vector<vector<int>> chains;
vector<int> chainIdx;
vector<SegmentTree<HLD_TREE>> chainST;
unordered_map<Edge,int,Edge::Hash> edgeMap;
int DFS(int head, int &t, int d){
    et.push_back(head);
    start[head]=++t;
    level[head]=d;
    int size = 1;
    int mxChildSize=0;
    for(int i = 0; i  < graph[head].size(); ++i){
        Edge &edge = edges[graph[head][i]];
        if(!visited[edge.v]){
            visited[edge.v]=1;
            parent[edge.v]=head;
            edgeMap.insert({edges[graph[head][i]],graph[head][i]});
            int childSize = DFS(edge.v,t,d+1);
            size+=childSize;
            if(childSize > mxChildSize){
                mxChildSize=childSize;
                heavyChild[head]=graph[head][i];
            }
            et.push_back(head);
            ++t;
        }
    }
    return size;
}
void HLD(int head, int rep){
    if(visited[head]) return;
    visited[head]=1;
    int edgeHead = edgeMap.find(Edge(parent[head],head))->second;
    if(edgeHead>=0){
        reps[edgeHead]=rep;
        chains[rep].push_back(edgeHead);
        chainIdx[edgeHead]=chains[rep].size()-1;
    }
    for(int i = 0; i < graph[head].size(); ++i){
        Edge &edge = edges[graph[head][i]];
        HLD(edge.v,graph[head][i]==heavyChild[head]?rep:graph[head][i]);
    }
}
int HLD_Query(int head, int lca){
    if(head==lca) return 0;
    int mx = 0;
    int edgeHead=edgeMap[Edge(parent[head],head)];
    int lcaEdge=edgeMap[edges[heavyChild[lca]]]; 
    int prevHead;
    do{
        prevHead=edgeHead;
        mx=max(mx,chainST[rep2Chain[reps[edgeHead]]].query<HLD_TREE>(chainIdx[lcaEdge!=-1?(reps[edgeHead]==reps[lcaEdge]?lcaEdge:reps[edgeHead]):reps[edgeHead]],chainIdx[edgeHead]));
        edgeHead=edgeMap[Edge(parent[edges[reps[edgeHead]].u],edges[reps[edgeHead]].u)];
        if(edgeHead<0) break;
}while(reps[edgeHead]!=reps[prevHead] && level[lca]<=level[edges[edgeHead].u]);
    return mx;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    graph.resize(n);
    level.resize(n);
    parent.resize(n);
    start.resize(n);
    visited.resize(n,0);
    heavyChild.resize(n);
    reps.resize(2*n);
    rep2Chain.resize(2*n);
    chainIdx.resize(2*n);
    chains.resize(2*n);
    edgeMap.reserve(200005);
    for(int i = 0; i < n-1; ++i){
        int a,b,c; cin>>a>>b>>c; --a,--b;
        edges.emplace_back(a,b,c);
        graph[a].push_back(edges.size()-1);
        edges.emplace_back(b,a,c);
        graph[b].push_back(edges.size()-1);
    }
    visited[0]=1;
    int time = -1;
    DFS(0,time,0);
    visited.assign(n,0);
    edgeMap.insert({Edge(0,0),-1});
    parent[0]=0;
    for(int i = 0; i < graph[0].size(); ++i)
        edgeMap.insert({edges[graph[0][i]],graph[0][i]});
    HLD(0,heavyChild[0]);
    for(int i = 0; i < 2*n; ++i){
        if(!chains[i].empty()){
            chainST.emplace_back(chains[i].size(),edges,chains[i]);
            rep2Chain[i]=chainST.size()-1;
        }
    }
    SegmentTree<LCA_TREE> LCAst(et.size(),level,et);
    int q; cin>>q;
    for(int i = 0; i < q; ++i){
        int T; cin>>T;
        if(T==1){
            //update
            int a,v; cin>>a>>v; --a;
            unordered_map<Edge,int,Edge::Hash>::iterator it = edgeMap.find(edges[2*a]);
            if(it==edgeMap.end()){
                it=edgeMap.find(Edge(edges[2*a].v,edges[2*a].u));
            }
            chainST[rep2Chain[reps[it->second]]].update(chainIdx[it->second],v);
        }else{
            //query
            int a,b; cin>>a>>b; --a,--b;
            if(a==b){cout<<"0\n"; continue;}
            if(start[a]>start[b]){
                int c = a;
                a = b;
                b = c;
            }
            int lca=LCAst.query<LCA_TREE>(start[a],start[b]);
            cout<<max(HLD_Query(a,lca),HLD_Query(b,lca))<<"\n";
        }
    }
}
/*
10
3 2 7
8 9 10
9 5 1
9 4 5
8 7 1
6 3 5
3 9 10
10 4 6
9 1 9
1
2 7 4
ans: 10

5
5 4 1
4 3 2
3 2 3
2 1 4
3
2 1 2
1 1 5
2 4 5

ans:
4
5

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
1
2 5 5
ans: 0

6
1 2 5
2 3 4
3 4 3
4 5 2
5 6 1
3
2 1 6
1 1 30
2 5 6

ans:
5
1

6
1 2 5
2 3 4
3 4 3
4 5 2
5 6 1
3
2 1 6
1 5 30
2 5 6
*/