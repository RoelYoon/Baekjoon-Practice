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
        LCA_Node(int i, int v):id(i),v(v){}
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
    int n;
    vector<conditional_t<T==LCA,LCA_Node,int>> st;
    LCA_T(LCA_Node) query(int p, int L, int R, int QL, int QR){
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
    public:
    SegmentTree(){}
    SegmentTree(int n,vector<int> &data, vector<int> &key):n(n),st(4*n){build(0,0,n-1,data,key);}
    LCA_T(int) query(int L, int R){
        return query(0,0,n-1,L,R).id;
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
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n;
    graph.resize(n);
    parent.resize(n);
    heavyChild.resize(n);
    start.resize(n);
    level.resize(n);
    chains.resize(n);
    chainIdx.resize(n);
    rep2Chain.resize(n);
    parent[0]=0;
    for(int i = 0; i < n-1; ++i){
        cin>>parent[i+1];
        graph[parent[i+1]].push_back(i+1);
        --parent[i+1];
    }
    DFS(0,0);
    HLD(0,0);
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
            cout<<lcaSt.query(start[a],start[b])<<"\n";
        }else{
            //update
            int p; cin>>p; --p;

        }
    }
}