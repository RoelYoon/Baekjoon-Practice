#include <iostream>
#include <vector>
using namespace std;
enum Type{
    LCA,
    SUM,
    MIN
};
template <Type T>
class SegmentTree{
    struct LCA_Node{
        int id;
        int v;
        LCA_Node(){}
        LCA_Node(int i, int v):id(i),v(v){}
        bool operator<(const LCA_Node &other) const {
            return v<other.v;
        }
    };
    struct MIN_Node{
        int id;
        int nodeId;
        bool v;
        MIN_Node(){}
        MIN_Node(int i, int n, bool v):id(i),nodeId(n),v(v){}
        void flip(){
            v=!v;
        }
        bool operator<(const MIN_Node &other) const {
            if(v==other.v){
                return id>other.id;
            }
            return (int)v>(int)other.v;
        }
    };
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    #define LCA_T(t) template <Type U=T> \
    typename enable_if<U==LCA,t>::type
    #define SUM_T(t) template <Type U=T> \
    typename enable_if<U==SUM,t>::type
    #define MIN_T(t) template <Type U=T> \
    typename enable_if<U==MIN,t>::type
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int n;
    vector<conditional_t<T==LCA,LCA_Node,conditional_t<T==SUM,int,MIN_Node>>> st;
    LCA_T(LCA_Node) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return LCA_Node(-1,1e9);
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    SUM_T(int) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR)+query(RC(p),mid+1,R,QL,QR);
    }
    MIN_T(MIN_Node) query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return MIN_Node(-1,-1,0);
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return min(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    LCA_T(void) build(int p, int L, int R, vector<int> &data, vector<int> &key){
        if(L==R){
            st[p]=LCA_Node(key[L],data[key[L]]);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data,key);
        build(RC(p),mid+1,R,data,key);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    SUM_T(void) build(int p, int L, int R){
        if(L==R){
            st[p]=1;
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid);
        build(RC(p),mid+1,R);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    MIN_T(void) build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=MIN_Node(L,data[L],1);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    SUM_T(void) update(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p]=0;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR);
        update(RC(p),mid+1,R,QL,QR);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    MIN_T(void) update(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p].flip();
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR);
        update(RC(p),mid+1,R,QL,QR);
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(){}
    template <Type U=T>
    SegmentTree(int n,vector<int> &data, vector<int> &key,typename enable_if<U==LCA,void>::type*a=0):n(n),st(4*n){build(0,0,n-1,data,key);}
    template <Type U=T>
    SegmentTree(int n,typename enable_if<U==SUM,void>::type*a=0):n(n),st(4*n){build(0,0,n-1);}
    template <Type U=T>
    SegmentTree(int n,vector<int> &data, typename enable_if<U==MIN,void>::type*a=0):n(n),st(4*n){build(0,0,n-1,data);}
    LCA_T(int) query(int L, int R){
        return query(0,0,n-1,L,R).id;
    }
    SUM_T(int) query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    MIN_T(int) query(int L, int R){
        return query(0,0,n-1,L,R).nodeId;
    }
    SUM_T(void) update(int p){
        update(0,0,n-1,p,p);
    }
    MIN_T(void) update(int p){
        update(0,0,n-1,p,p);
    }
};
vector<vector<int>> graph;
vector<int> parent;
vector<int> level;
vector<int> heavyChild;
vector<int> reps;
vector<int> start;
vector<int> et;
vector<vector<int>> chains;
vector<int> chainIdx;
vector<int> rep2Chain;
vector<bool> deleted;
vector<SegmentTree<SUM>> sumChainST;
vector<SegmentTree<MIN>> minChainST;
int DFS(int head, int d){
    level[head]=d;
    et.push_back(head);
    start[head]=et.size()-1;
    int size = 1;
    int mxChildSize=0;
    for(int i = 0; i < graph[head].size(); ++i){
        if(parent[head]==graph[head][i]) continue;
        int childSize = DFS(graph[head][i],d+1);
        size+=childSize;
        if(childSize>mxChildSize){
            mxChildSize=childSize;
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
    for(int i = 0; i < graph[head].size(); ++i){
        if(graph[head][i]==parent[head]) continue;
        HLD(graph[head][i],graph[head][i]==heavyChild[head]?rep:graph[head][i]);
    }
};
int LCA_HLD_Query(int head){
    int prevHead;
    do{
        prevHead=head;
        head=minChainST[rep2Chain[reps[head]]].query(chainIdx[reps[head]],chainIdx[head]);
        if(deleted[head]){
            head=parent[reps[head]];
        }else{
            return head;
        }
    }while(prevHead!=head);
    return -1;
}
int HLD_Query(int head, int lca){
    int prevHead;
    int sum = 0;
    do{
        prevHead=head;
        sum+=sumChainST[rep2Chain[reps[head]]].query(chainIdx[level[reps[head]]<level[lca]?lca:reps[head]],chainIdx[head]);
        head=parent[reps[head]];
    }while(reps[prevHead]!=reps[head] && level[head]>=level[lca]);
    return sum;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n;
    graph.resize(n);
    parent.resize(n);
    reps.resize(n);
    heavyChild.resize(n);
    start.resize(n);
    level.resize(n);
    chains.resize(n);
    chainIdx.resize(n);
    rep2Chain.resize(n);
    deleted.assign(n,0);
    parent[0]=0;
    for(int i = 0; i < n-1; ++i){
        cin>>parent[i+1];
        --parent[i+1];
        graph[parent[i+1]].push_back(i+1);
    }
    DFS(0,0);
    HLD(0,0);
    for(int i = 0; i < n; ++i){
        if(!chains[i].empty()){
            sumChainST.emplace_back(chains[i].size());
            minChainST.emplace_back(chains[i].size(),chains[i]);
            rep2Chain[i]=sumChainST.size()-1;
        }
    }
    SegmentTree<LCA> lcaSt(et.size(),level,et);
    cin>>q;
    for(int i = 0; i < q; ++i){
        int t; cin>>t;
        if(t==1){
            //query
            int a,b; cin>>a>>b; --a,--b;
            if(start[a]>start[b]){
                int c = a;
                a=b;
                b=c;
            }
            int lca = lcaSt.query(start[a],start[b]);
            if(deleted[lca])
                lca=LCA_HLD_Query(lca);
            cout<<HLD_Query(a,lca)+HLD_Query(b,lca)-2<<"\n";
        }else{
            //update
            int p; cin>>p; --p;
            deleted[p]=1;
            sumChainST[rep2Chain[reps[p]]].update(chainIdx[p]);
            minChainST[rep2Chain[reps[p]]].update(chainIdx[p]);
        }
    }
}
/*
8
1 5 2 1 2 5 5
7
2 4
1 7 6
2 5
1 3 8
1 8 6
2 2
1 4 6

8
1 5 2 1 2 5 5
5
1 1 8
1 3 8
1 4 1
2 2
1 1 4
*/