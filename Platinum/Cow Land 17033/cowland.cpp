#include <iostream>
#include <vector>
using namespace std;
enum Type{
    LCA,
    XOR
};
struct LCA_Node{
    int id;
    int val;
    LCA_Node(){}
    LCA_Node(int i, int v):id(i),val(v){}
    bool operator<(const LCA_Node &other) const {
        return val < other.val;
    }
};
template <Type type>
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    #define LCA_TPL template <Type T>
    #define XOR_TPL template <Type T>
    #define LCA_T(t) typename enable_if<T==LCA,t>::type
    #define XOR_T(t) typename enable_if<T==XOR,t>::type
    int n;
    vector<conditional_t<type==LCA,LCA_Node,int>> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    LCA_TPL
    LCA_T(LCA_Node) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return LCA_Node(-1,1e9);
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return min(query<LCA>(LC(p),L,mid,QL,QR),query<LCA>(RC(p),mid+1,R,QL,QR));
    }
    LCA_TPL
    LCA_T(void) build(int p, int L, int R, vector<int> &data, vector<int> &key){
        if(L==R){
            st[p]=LCA_Node(key[L],data[key[L]]);
            return;
        }
        int mid = (L+R)/2;
        build<LCA>(LC(p),L,mid,data,key);
        build<LCA>(RC(p),mid+1,R,data,key);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    XOR_TPL
    XOR_T(int) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return query<XOR>(LC(p),L,mid,QL,QR) ^ query<XOR>(RC(p),mid+1,R,QL,QR);
    }
    XOR_TPL
    XOR_T(void) update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]=u;
            return;
        }
        int mid = (L+R)/2;
        update<XOR>(LC(p),L,mid,QL,QR,u);
        update<XOR>(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]^st[RC(p)];
    }
    XOR_TPL
    XOR_T(void) build(int p, int L, int R, vector<int> &data, vector<int> &key){
        if(L==R){
            st[p]=data[key[L]];
            return;
        }
        int mid = (L+R)/2;
        build<XOR>(LC(p),L,mid,data,key);
        build<XOR>(RC(p),mid+1,R,data,key);
        st[p]=st[LC(p)]^st[RC(p)];
    }
    public:
    SegmentTree(){}
    template <Type T=type>
    SegmentTree(int n, vector<int> &data, vector<int> &key, LCA_T(void)*a=0):n(n),st(4*n){build<LCA>(0,0,n-1,data,key);}
    template <Type T=type>
    SegmentTree(int n, vector<int> &data, vector<int> &key, XOR_T(void)*a=0):n(n),st(4*n){build<XOR>(0,0,n-1,data,key);}
    LCA_TPL
    LCA_T(int) query(int L, int R){
        return query<LCA>(0,0,n-1,L,R).id;
    }
    XOR_TPL
    XOR_T(int) query(int L, int R){
        return query<XOR>(0,0,n-1,L,R);
    }
    XOR_TPL
    XOR_T(void) update(int L, int R, int u){
        update<XOR>(0,0,n-1,L,R,u);
    }
};
vector<int> fun;
vector<vector<int>> graph;
vector<bool> visited;
vector<int> level;
vector<int> parent;
vector<int> heavyChild;
vector<int> reps;
vector<int> chainIdx;
vector<int> rep2Chain;
vector<vector<int>> chains;
vector<SegmentTree<XOR>> chainST;
vector<int> et;
vector<int> start;
int DFS(int head, int &t, int d){
    et.push_back(head);
    start[head]=++t;
    level[head]=d;
    int size = 1;
    int mxChildSize=0;
    for(int i = 0; i < graph[head].size(); ++i){
        if(!visited[graph[head][i]]){
            visited[graph[head][i]]=1;
            parent[graph[head][i]]=head;
            int childSize = DFS(graph[head][i],t,d+1);
            size+=childSize;
            if(childSize>mxChildSize){
                mxChildSize=childSize;
                heavyChild[head]=i;
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
    reps[head]=rep;
    chains[rep].push_back(head);
    chainIdx[head]=chains[rep].size()-1;
    for(int i = 0; i < graph[head].size(); ++i)
        HLD(graph[head][i],i==heavyChild[head]?rep:graph[head][i]);
}
int HLD_Query(int head, int lca, bool noLCA){
    int x = 0;
    int prevHead;
    do{
        prevHead=head;
        x^=chainST[rep2Chain[reps[head]]].query<XOR>(chainIdx[reps[head]==reps[lca]?lca:reps[lca]]+(reps[head]==reps[lca]&&noLCA?1:0),chainIdx[head]);
        head=parent[reps[head]];
    }while(reps[head]!=reps[prevHead]);
    return x;
}
void pA(vector<int> &a){
    for(int i = 0; i < a.size(); ++i){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    fun.resize(n);
    graph.resize(n);
    visited.resize(n);
    level.resize(n);
    parent.resize(n);
    heavyChild.resize(n);
    reps.resize(n);
    chainIdx.resize(n);
    rep2Chain.resize(n);
    chains.resize(n);
    start.resize(n);
    for(int i = 0; i < n; ++i){
        cin>>fun[i];
    }
    for(int i = 0; i < n-1; ++i){
        int a,b; cin>>a>>b; --a,--b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int time=-1;
    visited[0]=1;
    DFS(0,time,0);
    visited.assign(n,0);
    HLD(0,0);
    for(int i = 0; i < n; ++i){
        if(!chains[i].empty()){
            chainST.emplace_back(chains[i].size(),fun,chains[i]);
            rep2Chain[i]=chainST.size()-1;
        }
    }
    SegmentTree<LCA> LCAst(et.size(),level,et);
    for(int i = 0; i < q; ++i){
        int t; cin>>t;
        if(t==1){
            //update
            int a,v; cin>>a>>v; --a;
            chainST[rep2Chain[reps[a]]].update<XOR>(chainIdx[a],chainIdx[a],v);
        }else{
            //query
            int a,b; cin>>a>>b; --a,--b;
            if(start[a]>start[b]){
                int c=a;
                a=b;
                b=c;
            }
            int lca = LCAst.query<LCA>(start[a],start[b]);
            cout<<(HLD_Query(a,lca,0)^HLD_Query(b,lca,1))<<"\n";
        }
    }
}