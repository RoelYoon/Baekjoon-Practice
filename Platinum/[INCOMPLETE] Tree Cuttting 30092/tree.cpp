#include <iostream>
#include <vector>
using namespace std;
enum Type{
    LCA,
    SUM
};
template <Type T>
class SegmentTree{
    struct LCA_Node{
        int id;
        int v;
        LCA_Node(){}
        LCA_Node(int i, int v):id(i),v(v){};
        bool operator<(const LCA_Node &other) const {
            return v<other.v;
        }
    };
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    #define LCA_T(t) template <Type U=T> \
    typename enable_if<U==LCA,t>::type
    #define SUM_T(t) template <Type U=T> \
    typename enable_if<U==SUM,t>::type
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<conditional_t<T==LCA,LCA_Node,int>> st;
    conditional_t<T==SUM,vector<bool>,void*> lazy;
    conditional_t<T==SUM,vector<int>,void*> upd;
    LCA_T(void) build(int p, int L, int R, vector<int>&data, vector<int>&key){
        if(L==R){
            st[p]=LCA_Node(key[L],data[key[L]]);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data,key);
        build(RC(p),mid+1,R,data,key);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    LCA_T(LCA_Node) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return LCA_Node(-1,1e9);
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    SUM_T(void) propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]=upd[p]*(R-L+1);
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]+=upd[p];
                upd[RC(p)]+=upd[p];
            }
            lazy[p]=0;
            upd[p]=0;
        }
    }
    SUM_T(int) query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid=(L+R)/2;
        return query(LC(p),L,mid,QL,QR)+query(RC(p),mid+1,R,QL,QR);
    }
    SUM_T(void) update(int p, int L, int R, int QL, int QR, int u){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]=u;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(){}
    template <Type U=T>
    SegmentTree(int n,vector<int> &data, vector<int> &key, typename enable_if<U==LCA,void>::type*a=0):n(n),st(4*n){build(0,0,n-1,data,key);}
    template <Type U=T>
    SegmentTree(int n,typename enable_if<U==SUM,void>::type*a=0):n(n),st(4*n),lazy(4*n),upd(4*n){}
    LCA_T(int) query(int L, int R){
        return query(0,0,n-1,L,R).id;
    }
    SUM_T(int) query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    SUM_T(void) update(int L, int R, int u){
        update(0,0,n-1,L,R,u);
    }
};
vector<vector<int>> graph;
vector<int> parent;
vector<int> level;
vector<int> heavyChild;
vector<int> et;
vector<int> start;
vector<vector<int>> chains;
vector<int> chainIdx;
vector<int> reps;
vector<int> rep2Chain;
vector<SegmentTree<SUM>> chainST;
int DFS(int head, int d){
    et.push_back(head);
    start[head]=et.size()-1;
    level[head]=d;
    int size=1;
    int maxChildSize=0;
    for(int i = 0; i < graph[head].size(); ++i){
        if(graph[head][i]==parent[head]) continue;
        parent[graph[head][i]]=head;
        int childSize = DFS(graph[head][i],d+1);
        if(childSize>maxChildSize){
            maxChildSize=childSize;
            heavyChild[head]=graph[head][i];
        }
        et.push_back(head);
    }
    return size;
}
void HLD(int head, int rep){
    reps[head]=rep;
    chains[rep].push_back(head);
    chainIdx[head]=chains[rep].size()-1;
    for(int i = 0; i < graph[head][i]; ++i){
        if(graph[head][i]==parent[head]) continue;
        HLD(graph[head][i],);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    graph.resize(n);
    parent.resize(n); parent[0]=0;
    level.resize(n);
    heavyChild.resize(n);
    start.resize(n);
    chains.resize(n);
    chainIdx.resize(n);
    reps.resize(n);
    rep2Chain.resize(n);
    for(int i = 0; i < n-1; ++i){
        int a,b; cin>>a>>b; --a,--b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    DFS(0,0);

    SegmentTree<LCA> lcaST(et.size(),level,et);
    for(int i = 0; i < q; ++i){
        int a,b,c,d; cin>>a>>b>>c>>d;
        --a,--b,--c,--d;
        if(start[a]>start[b]){
            int t=a;
            a=b;
            b=t;
        }
        if(start[c]>start[d]){
            int t=c;
            c=d;
            d=t;
        }
        int lca1 = lcaST.query(start[a],start[b]);
        int lca2 = lcaST.query(start[c],start[d]);
        cout<<lca1+1<<" "<<lca2+1<<"\n";
    }
}