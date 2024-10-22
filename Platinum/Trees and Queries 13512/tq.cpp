#include <iostream>
#include <vector>
using namespace std;
// white - 0
// black - 1 
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    struct Node{
        int id;
        int num;
        bool v;
        Node(){}
        Node(int i, bool v, int num):id(i),v(v),num(num){}
        void flip(){
            v=!v;
        }
        bool operator<(const Node &other) const {
            if(v==other.v){
                //both black
                return id>other.id;
            }
            return (int)v<(int)other.v;
        }
    };
    int n;
    vector<Node> st;
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=Node(L,0,data[L]);
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=max(st[LC(p)],st[RC(p)]);
    }
    Node query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return Node(1e9,0,-1);
        if(inBounds(L,R,QL,QR))
            return st[p];
        int mid = (L+R)/2;
        return max(query(LC(p),L,mid,QL,QR),query(RC(p),mid+1,R,QL,QR));
    }
    void update(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            st[p].flip();
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR);
        update(RC(p),mid+1,R,QL,QR);
        st[p]=max(st[LC(p)],st[RC(p)]);
    }
    public:
    SegmentTree(int n, vector<int> &data):n(n),st(4*n){build(0,0,n-1,data);}
    SegmentTree(){}
    int query(int L, int R){
        Node qNode = query(0,0,n-1,L,R);
        return qNode.v?qNode.num:-1;
    }
    void update(int p){
        update(0,0,n-1,p,p);
    }
};
vector<vector<int>> graph;
vector<bool> visited;
vector<int> parent;
vector<int> level;
vector<int> heavyChild;
vector<int> reps;
vector<vector<int>> chains;
vector<int> chainIdx;
vector<int> rep2Chain;
vector<SegmentTree> chainSt;
int DFS(int head, int d){
    level[head]=d;
    int size = 1;
    int maxSize = 0;
    for(int i = 0; i < graph[head].size(); ++i){
        if(visited[graph[head][i]]) continue;
        visited[graph[head][i]]=1;
        int childSize = DFS(graph[head][i],d+1);
        parent[graph[head][i]]=head;
        size+=childSize;
        if(childSize>maxSize){
            maxSize=childSize;
            heavyChild[head]=graph[head][i];
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
    for(int i = 0; i < graph[head].size(); ++i){
        HLD(graph[head][i],graph[head][i]==heavyChild[head]?rep:graph[head][i]);
    }
}
int HLD_Query(int head){
    int prevHead;
    int result=-1;
    do{
        int Q = chainSt[rep2Chain[reps[head]]].query(chainIdx[reps[head]],chainIdx[head]);
        if(Q!=-1){
            result=Q+1;
        }
        prevHead=head;
        head=parent[reps[head]];
    }while(head!=prevHead);
    return result;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n;
    graph.resize(n);
    parent.resize(n);
    level.resize(n);
    heavyChild.resize(n);
    visited.resize(n);
    reps.resize(n);
    chains.resize(n);
    chainIdx.resize(n);
    rep2Chain.resize(n);
    for(int i = 0; i < n-1; ++i){
        int a,b; cin>>a>>b; --a,--b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    visited[0]=1;
    parent[0]=0;
    DFS(0,0);
    visited.assign(n,0);
    HLD(0,0);
    for(int i = 0; i < n; ++i){
        if(!chains[i].empty()){
            chainSt.emplace_back(chains[i].size(), chains[i]);
            rep2Chain[i]=chainSt.size()-1;
        }
    }
    cin>>q;
    for(int i = 0; i < q; ++i){
        int T, u; cin>>T>>u; --u;
        if(T==1){
            //update
            chainSt[rep2Chain[reps[u]]].update(chainIdx[u]);
        }else{
            //query
            cout<<HLD_Query(u)<<"\n";
        }
    }
}
/*
9
1 2
1 3
2 4
2 9
5 9
7 9
8 9
6 8
6
1 9
2 6
1 2
2 6
1 8
2 6

4
1 2
1 3
1 4
6
2 1
2 2
2 3
2 4
1 4
2 4
*/