#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <type_traits>
using namespace std;
struct LCA_Node{
    int id;
    int val;
    LCA_Node(){}
    LCA_Node(int id, int v):id(id),val(v){}
    LCA_Node(int v):val(v){}
    bool operator<(const LCA_Node &other) const {
        return val<other.val;
    }
};
struct MS_Node{ //merge sort tree node
    vector<int> val;
    MS_Node(){}
    MS_Node(vector<int> &data, vector<int> *e, int L, int R){
        for(int i = L; i <=R; ++i){
            val.push_back(data[(*e)[i]]);
        }
        sort(val.begin(),val.end());
    }
    MS_Node(const vector<int> &a, const vector<int> &b){
        int pa = 0;
        int pb = 0;
        while(pa < a.size() && pb < b.size()){
            if(a[pa]<b[pb]){
                val.push_back(a[pa++]);
            }else{
                val.push_back(b[pb++]);
            }
        }
        while(pa < a.size())
            val.push_back(a[pa++]);
        while(pb < b.size())
            val.push_back(b[pb++]);
    }
    MS_Node operator+(const MS_Node &other) const {
        return MS_Node(val,other.val);
    }
};
template <typename Node>
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<Node> st;
    inline bool outBounds(int L, int R, int QL, int QR){return R<QL || L>QR;}
    inline bool inBounds(int L, int R, int QL, int QR){return L>=QL && R<=QR;}
    template<typename T>
    typename enable_if<is_same<T, LCA_Node>::value,void>::type
    assignBase(int p, int L, int R, vector<int> &data, vector<int> *e){
        st[p]=Node((*e)[L],data[(*e)[L]]);
    }
    template<typename T>
    typename enable_if<is_same<T, MS_Node>::value,void>::type
    assignBase(int p, int L, int R, vector<int> &data, vector<int> *e){
        st[p]=Node(data,e,L,R);
    }
    template<typename T>
    typename enable_if<is_same<T, LCA_Node>::value,void>::type
    assign(int p, int L, int R, vector<int> &data, vector<int> *e){
        st[p]=min(st[LC(p)],st[RC(p)]);
    }
    template<typename T>
    typename enable_if<is_same<T, MS_Node>::value,void>::type
    assign(int p, int L, int R, vector<int> &data, vector<int> *e){
        st[p]=st[LC(p)]+st[RC(p)];
    }
    void build(int p, int L, int R, vector<int> &data,vector<int> *e){
        if(L==R){
            assignBase<Node>(p,L,R,data,e);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data,e);
        build(RC(p),mid+1,R,data,e);
        assign<Node>(p,L,R,data,e);
    }
    template<typename T>
    typename enable_if<is_same<T, LCA_Node>::value, Node>::type
    query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return Node(1e9);
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return min(query<LCA_Node>(LC(p),L,mid,QL,QR),query<LCA_Node>(RC(p),mid+1,R,QL,QR));
    }
    template<typename T>
    typename enable_if<is_same<T, MS_Node>::value, bool>::type
    query(int p, int L, int R, int QL, int QR, int K){
        if(outBounds(L,R,QL,QR))
            return 0;
        if(inBounds(L,R,QL,QR)){
            vector<int>::iterator it = lower_bound(st[p].val.begin(),st[p].val.end(),K);
            return it==st[p].val.end()?0:*it==K;
        }
        int mid = (L+R)/2;
        return query<MS_Node>(LC(p),L,mid,QL,QR,K) || query<MS_Node>(RC(p),mid+1,R,QL,QR,K);
    }
    public:
    SegmentTree(int n, vector<int> &data,vector<int> *e=nullptr):n(n),st(4*n){build(0,0,n-1,data,e);}
    template<typename T>
    typename enable_if<is_same<T, LCA_Node>::value, int>::type query(int L, int R){
        return query<LCA_Node>(0,0,n-1,L,R).id;
    }
    template<typename T>
    typename enable_if<is_same<T, MS_Node>::value, bool>::type query(int L, int R, int K){
        return query<MS_Node>(0,0,n-1,L,R,K);
    }
};
int DFS(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &level, vector<int> &parent,vector<int> &sizes, vector<int> &mxChild, vector<int> &start, vector<int> &et, int head, int &t, int d){
    et.push_back(head);
    ++t;
    start[head]=t;
    level[head]=d;
    int size = 1;
    int mxChildSize = 0;
    mxChild[head]=-1;
    for(int i = 0; i < graph[head].size(); ++i){
        if(!visited[graph[head][i]]){
            visited[graph[head][i]]=1;
            parent[graph[head][i]]=head;
            int childSize=DFS(graph,visited,level,parent,sizes,mxChild,start,et,graph[head][i],t,d+1);
            size+=childSize;
            if(childSize > mxChildSize){
                mxChildSize = childSize;
                mxChild[head]=i;
            }
            et.push_back(head);
            ++t;
        }
    }
    return sizes[head]=size;
}
void HLD(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &level, vector<int> &reps, vector<int> &chainIdx, vector<int> &sizes, vector<int> &mxChild, vector<vector<int>> &chains, int head, int rep){
    if(visited[head]) return;
    visited[head]=1;
    reps[head]=rep;
    chains[rep].push_back(head);
    chainIdx[head]=chains[rep].size()-1;
    for(int i = 0; i < graph[head].size(); ++i)
        HLD(graph,visited,level,reps,chainIdx,sizes,mxChild,chains,graph[head][i],(i==mxChild[head] ? rep : graph[head][i]));
}
bool HLD_query(vector<SegmentTree<MS_Node>> &chainST, vector<int> &parent, vector<int> &level,vector<int> &reps, vector<int> &repChain, vector<int> &chainIdx, int head, int LCA, int t){
    do{
        if(chainST[repChain[reps[head]]].query<MS_Node>(chainIdx[reps[LCA]==reps[head]?LCA:reps[head]],chainIdx[head],t))
            return 1;
        head=parent[reps[head]];
    }while(parent[head]!=head && level[LCA]<=level[head]);
    return 0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    vector<int> type(n);
    vector<vector<int>> graph(n);
    vector<bool> visited(n);
    vector<int> start(n);
    vector<int> et;
    vector<int> level(n);
    vector<int> reps(n);
    vector<int> chainIdx(n);
    vector<int> parent(n);
    vector<int> sizes(n);
    vector<int> mxChild(n);
    vector<vector<int>> chains(n);
    for(int i = 0; i < n; ++i){
        cin>>type[i];
        --type[i];
    }
    for(int i = 0; i < n-1; ++i){
        int a,b; cin>>a>>b; --a,--b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int t = -1;
    visited[0]=1;
    parent[0]=0;
    DFS(graph,visited,level,parent,sizes,mxChild,start,et,0,t,0);
    visited.assign(n,0);
    HLD(graph,visited,level,reps,chainIdx,sizes,mxChild,chains,0,0);
    vector<SegmentTree<MS_Node>> chainST;
    vector<int> repChain(n);
    for(int i = 0; i < n; ++i){
        if(!chains[i].empty()){
            chainST.emplace_back(chains[i].size(),type,&chains[i]);
            repChain[i]=chainST.size()-1;
        }
    }
    SegmentTree<LCA_Node> LCAst(2*n,level,&et);
    string ans(q,'0'); ans+="\n";
    for(int i = 0; i < q; ++i){
        int a,b,T; cin>>a>>b>>T; --a,--b,--T;
        if(start[a]>start[b]){
            int t = a;
            a = b;
            b = t;
        }
        int LCA = LCAst.query<LCA_Node>(start[a],start[b]);
        ans[i]=(HLD_query(chainST,parent,level,reps,repChain,chainIdx,a,LCA,T) || HLD_query(chainST,parent,level,reps,repChain,chainIdx,b,LCA,T) ? '1' : '0');
    }
    cout<<ans;
}