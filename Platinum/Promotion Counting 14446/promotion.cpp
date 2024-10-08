#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define MAX 100000
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<int> st;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return st[p];
        }
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR)+query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            st[p]+=u;
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR,u);
        update(RC(p),mid+1,R,QL,QR,u);
        st[p]=st[LC(p)]+st[RC(p)];
    }
    public:
    SegmentTree(int n):n(n),st(4*n){}
    int query(int L, int R){
        return query(0,0,n-1,L,R);
    }
    void update(int P, int U){
        update(0,0,n-1,P,P,U);
    }
};
struct Query{
    int L;
    int R;
    int id;
    Query(){}
    Query(int l, int r, int id):L(l),R(r),id(id){}
};
void eulerTour(vector<vector<int>> &graph, vector<int> &start, vector<int> &end, vector<int> &et,int head, int &t){
    start[head]=++t;
    et[start[head]]=head;
    for(int i = 0; i < graph[head].size(); ++i)
        eulerTour(graph,start,end,et,graph[head][i],t);
    end[head]=t;
}
Query qs[MAX];
int ans[MAX];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,s; cin>>n;
    s=sqrt(n);
    vector<vector<int>> graph(n);
    vector<int> pc(n),pcZIP(n),start(n),end(n),et(n);
    for(int i = 0; i < n; ++i){
        cin>>pc[i];
        pcZIP[i]=pc[i];
    }
    sort(pcZIP.begin(),pcZIP.end());
    pcZIP.erase(unique(pcZIP.begin(),pcZIP.end()),pcZIP.end());
    for(int i = 0; i < n; ++i)
        pc[i]=lower_bound(pcZIP.begin(),pcZIP.end(),pc[i])-pcZIP.begin();
    for(int i = 1; i < n; ++i){
        int p; cin>>p; --p;
        graph[p].push_back(i);
    }
    int time = -1;
    eulerTour(graph,start,end,et,0,time);
    for(int i = 0; i < n; ++i){
        qs[i].L=start[i];
        qs[i].R=end[i];
        qs[i].id=i;
    }
    sort(qs,qs+n,[s](const Query &a, const Query &b){
        if(a.L/s != b.L/s) return a.L < b.L;
        return a.L/s % 2 ? a.R > b.R : a.R < b.R;
    });
    SegmentTree st(n);
    int L=0, R=-1;
    for(int i = 0; i < n; ++i){
        const int QL = qs[i].L, QR = qs[i].R, K = pc[qs[i].id];
        //expand
        while(L > QL){
            st.update(pc[et[--L]],1);
        }
        while(R < QR){
            st.update(pc[et[++R]],1);
        }
        //shrink
        while(L < QL){
            st.update(pc[et[L++]],-1);
        }
        while(R > QR){
            st.update(pc[et[R--]],-1);
        }
        ans[qs[i].id]=st.query(K+1,n-1);
    }
    for(int i = 0; i < n; ++i)
        cout<<ans[i]<<"\n";
}