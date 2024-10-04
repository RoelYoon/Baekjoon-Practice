#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<int> st;
    vector<bool> lazy;
    vector<int> upd;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L > QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L >= QL && R <= QR;
    }
    void build(int p, int L, int R, vector<int> &data){
        if(L==R){
            st[p]=data[L];
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,data);
        build(RC(p),mid+1,R,data);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    void propagate(int p, int L, int R){
        if(lazy[p]){
            st[p]+=upd[p];
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]+=upd[p];
                upd[RC(p)]+=upd[p];
            }
            lazy[p]=0;
            upd[p]=0;
        }
    }
    int query(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR) + query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]+=u;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n, vector<int> &data):n(n),st(4*n),lazy(4*n),upd(4*n){build(0,0,n-1,data);}
    int query(int p){
        return query(0,0,n-1,p,p);
    }
    void update(int L, int R, int u){
        update(0,0,n-1,L,R,u);
    }
};
void eulerTour(vector<vector<int>> &graph, vector<int> &start, vector<int> &end, int head, int &time){
    start[head]=time++;
    for(int i = 0; i < graph[head].size(); ++i){
        int v = graph[head][i];
        eulerTour(graph,start,end,v,time);
    }
    end[head]=time;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,m,time=0; cin>>n>>m;
    vector<vector<int>> graph(n);
    vector<int> start(n);
    vector<int> end(n);
    vector<int> wages(n);
    vector<int> eWages(n);
    cin>>wages[0];
    for(int i = 1; i < n; ++i){
        int p;
        cin>>wages[i]>>p;
        graph[p-1].push_back(i);
    }
    eulerTour(graph,start,end,0,time);
    for(int i = 0; i < n; ++i)
        eWages[start[i]]=wages[i];
    SegmentTree st(n,eWages);
    for(int i = 0; i < m; ++i){
        char t;
        int p; cin>>t>>p; --p;
        if(t=='p'){
            //update
            int u; cin>>u;
            st.update(start[p]+1,end[p]-1,u);
        }else{
            cout<<st.query(start[p])<<"\n";
        }
    }
}