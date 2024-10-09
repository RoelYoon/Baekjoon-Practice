#include <iostream>
#include <vector>
#include <type_traits>
#include <unordered_map>
#define ll long long
using namespace std;
struct LCA{
    int id;
    int val;
    LCA():id(-1),val(1e9){}
    LCA(int id, int v):id(id),val(v){}
    bool operator<(const LCA &other) const {
        return val<other.val;
    }
};
template <typename T>
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    #define LCA_FT(t) template <typename U=T> \
    typename enable_if<is_same<U,LCA>::value,t>::type 
    #define CHAIN_FT(t) template <typename U=T> \
    typename enable_if<is_same<U,ll>::value,t>::type 
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<conditional_t<is_same<T,LCA>::value, LCA, ll>> st;
    conditional_t<is_same<T,LCA>::value,void*,vector<bool>> lazy;
    conditional_t<is_same<T,LCA>::value,void*,vector<int>> upd;
    LCA_FT(void) build(int p, int L, int R, vector<int> &data, vector<int> &key){
        if(L==R){
            st[p]=LCA(key[L],data[key[L]]);
            return;
        }
        int mid = (L+R)/2;
        build<LCA>(LC(p),L,mid,data,key);
        build<LCA>(RC(p),mid+1,R,data,key);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    LCA_FT(LCA) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return LCA(-1,1e9);
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return min(query<LCA>(LC(p),L,mid,QL,QR),query<LCA>(RC(p),mid+1,R,QL,QR));
    }
    CHAIN_FT(void) propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]+=(ll)(R-L+1)*(ll)upd[p];
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]+=upd[p];
                upd[RC(p)]+=upd[p];
            }
            lazy[p]=0;
            upd[p]=0;
        }
    }
    CHAIN_FT(ll) query(int p, int L, int R, int QL, int QR){
        propagate<ll>(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return query<ll>(LC(p),L,mid,QL,QR)+query<ll>(RC(p),mid+1,R,QL,QR);
    }
    CHAIN_FT(void) update(int p, int L, int R, int QL, int QR, int u){
        propagate<ll>(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]+=u;
            propagate<ll>(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update<ll>(LC(p),L,mid,QL,QR,u);
        update<ll>(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(){}
    SegmentTree(int n, vector<int> &data, vector<int> &key):n(n),st(4*n){build<LCA>(0,0,n-1,data,key);}
    SegmentTree(int n):n(n),st(4*n),lazy(4*n),upd(4*n){}
    LCA_FT(int) query(int L, int R){
        return query<LCA>(0,0,n-1,L,R).id;
    }
    CHAIN_FT(ll) query(int L, int R){
        if(L>R){int c = L; L = R; R = c;}
        return query<ll>(0,0,n-1,L,R);
    }
    CHAIN_FT(void) update(int L, int R, int u){
        if(L>R){int c = L; L = R; R = c;}
        update<ll>(0,0,n-1,L,R,u);
    }
};
struct Edge{
    int u;
    int v;
    Edge(int u, int v):u(u),v(v){}
    struct Hash{
        size_t operator()(const Edge &a) const {
            return hash<int>{}(a.u) ^ hash<int>{}(a.v); 
        }
    };
    bool operator==(const Edge &other) const {
        return u==other.u && v==other.v;
    }
};
vector<vector<int>> graph;
vector<Edge> edges;
vector<bool> visited;
vector<int> et;
vector<int> start;
vector<int> sizes;
vector<int> heavyChildI;
vector<int> parent;
vector<int> level;
vector<int> reps;
vector<int> repToChain;
vector<int> chainIdx;
vector<vector<int>> chains;
vector<SegmentTree<ll>> chainST;
unordered_map<Edge,int,Edge::Hash> edgeMap;
int DFS(int head, int &t, int d){
    et.push_back(head);
    start[head]=++t;
    level[head]=d;
    int size = 1;
    int mxChildSize = 0;
    for(int i = 0; i < graph[head].size(); ++i){
        if(!visited[graph[head][i]]){
            visited[graph[head][i]]=1;
            parent[graph[head][i]]=head;
            edges.emplace_back(head,graph[head][i]);
            int edgePos = edges.size()-1;
            edgeMap.insert({edges[edgePos],edgePos});
            int childSize = DFS(graph[head][i],t,d+1);
            size+=childSize;
            if(childSize>mxChildSize){
                mxChildSize=childSize;
                heavyChildI[head]=edgePos;
            }
            et.push_back(head);
            ++t;
        }
    }
    return sizes[head]=size;
}
void HLD(int head, int rep){
    for(int i = 0; i < graph[head].size(); ++i){
        if(!visited[graph[head][i]]){
            visited[graph[head][i]]=1;
            int edgeID = edgeMap.find(Edge(head,graph[head][i]))->second;
            int childRep = edgeID==heavyChildI[head] ? rep : edgeID;
            reps[edgeID]=childRep;
            chains[childRep].push_back(edgeID);
            chainIdx[edgeID]=chains[childRep].size()-1;
            HLD(graph[head][i],childRep);
        }
    }
}
int HLD_query(int head, int LCA){
    int sum = 0;
    int prevHead;
    do{
        sum+=chainST[repToChain[reps[head]]].query<ll>(chainIdx[reps[head]==reps[heavyChildI[LCA]]?heavyChildI[LCA]:reps[head]],chainIdx[head]);
        prevHead = head;
        int rp = parent[edges[reps[head]].u];
        head=edgeMap.find(Edge(rp,edges[reps[head]].u==0 ? edges[reps[head]].v : edges[reps[head]].u))->second;
    }while(reps[prevHead]!=reps[head] && level[LCA]<=level[edges[head].u]);
    return sum;
}
void HLD_update(int head, int LCA, int u){
    int prevHead;
    do{
        chainST[repToChain[reps[head]]].update<ll>(chainIdx[reps[head]==reps[heavyChildI[LCA]]?heavyChildI[LCA]:reps[head]],chainIdx[head],u);
        prevHead = head;
        int rp = parent[edges[reps[head]].u];
        head=edgeMap.find(Edge(rp,edges[reps[head]].u==0 ? edges[reps[head]].v : edges[reps[head]].u))->second;
    }while(reps[prevHead]!=reps[head] && level[LCA]<=level[edges[head].u]);
}
void pA(vector<int> &a){
    for(int i = 0; i < a.size(); ++i){
        cout<<a[i]<<" ";
    }cout<<"\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    graph.resize(n);
    visited.assign(n,0);
    start.resize(n);
    sizes.resize(n);
    heavyChildI.resize(n);
    parent.resize(n);
    level.resize(n);
    reps.resize(n);
    repToChain.resize(n);
    chainIdx.resize(n);
    chains.resize(n);
    for(int i = 0; i < n-1; ++i){
        int a,b; cin>>a>>b; --a,--b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int time = -1;
    visited[0]=1;
    parent[0]=0;
    DFS(0,time,0);
    visited.assign(n,0);
    visited[0]=1;
    HLD(0,heavyChildI[0]);
    for(int i = 0; i < n; ++i){
        if(!chains[i].empty()){
            chainST.emplace_back(chains[i].size());
            repToChain[i]=chainST.size()-1;
        }
    }
    SegmentTree<LCA> LCAst(2*n,level,et);
    for(int i = 0; i < q; ++i){
        char t; int a,b; cin>>t>>a>>b; --a,--b;
        if(a==b){if(t=='Q') cout<<"0\n";continue;}
        if(start[a]>start[b]){
            int c = a;
            a = b;
            b = c;
        }
        int lca = LCAst.query<LCA>(start[a],start[b]);
        bool aIsLCA=a==lca;
        if(a!=lca)
            a=edgeMap.find(Edge(parent[a],a))->second;
        b=edgeMap.find(Edge(parent[b],b))->second;
        if(t=='P'){
            if(!aIsLCA)
                HLD_update(a,lca,1);
            HLD_update(b,lca,1);
        }else{
            cout<<(!aIsLCA?HLD_query(a,lca):0)+HLD_query(b,lca)<<"\n";
        }
    }
}
/*
5 6
1 2
2 3
3 4
4 5
P 1 5
P 1 4
P 1 3
P 1 2
P 1 1
Q 1 5
-ANS: 10
3 3
1 2
2 3
P 1 3
P 1 2
Q 1 3
-ANS: 3
*/