#include <iostream>
#include <vector>
using namespace std;
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<vector<int>> st;
    vector<bool> lazy;
    vector<int> upd;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R<QL || L>QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    void build(int p, int L, int R, string &s){
        if(L==R){
            st[p][s[L]-'0'] = 1;
            return;
        }
        int mid = (L+R)/2;
        build(LC(p),L,mid,s);
        build(RC(p),mid+1,R,s);
        for(int i = 0; i <= 9; ++i)
            st[p][i] = st[LC(p)][i] + st[RC(p)][i];
    }
    void propagate(int p, int L, int R){
        if(lazy[p]){
            int updArr[10]{};
            for(int i = 0; i <= 9; ++i){
                updArr[(i+upd[p])%10] = st[p][i];
            }
            for(int i = 0; i <= 9; ++i)
                st[p][i] = updArr[i];
            if(L!=R){
                lazy[LC(p)]=lazy[RC(p)]=1;
                upd[LC(p)]+=upd[p];
                upd[RC(p)]+=upd[p];
            }
            lazy[p]=0;
            upd[p]=0;
        }
    }
    void query(int p, int L, int R, int QL, int QR, int v[]){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR))
            return;
        if(inBounds(L,R,QL,QR)){
            for(int i = 0; i <= 9; ++i)
                v[i] = st[p][i];
            return;
        }
        int mid = (L+R)/2;
        int q1[10]{};
        query(LC(p),L,mid,QL,QR,q1);
        int q2[10]{};
        query(RC(p),mid+1,R,QL,QR,q2);
        for(int i = 0; i <= 9; ++i)
            v[i] = q1[i]+q2[i];
    }
    void update(int p, int L, int R, int QL, int QR){
        propagate(p,L,R);
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            lazy[p]=1;
            upd[p]++;
            propagate(p,L,R);
            return;
        }
        int mid = (L+R)/2;
        update(LC(p),L,mid,QL,QR);
        update(RC(p),mid+1,R,QL,QR);
        for(int i = 0; i <= 9; ++i)
            st[p][i] = st[LC(p)][i] + st[RC(p)][i];
    };
    public:
    SegmentTree(string &s):n(s.size()),st(4*n,vector<int>(10)),lazy(4*n),upd(4*n){build(0,0,n-1,s);}
    int query(int L, int R){
        int v[10]{};
        query(0,0,n-1,L,R,v);
        int ans = 0;
        for(int i = 0; i <= 9; ++i)
            ans+=v[i]*i;
        return ans;
    };
    void update(int L, int R){
        update(0,0,n-1,L,R);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin>>n>>q;
    string s; cin>>s;
    SegmentTree st(s);
    for(int i = 0; i < q; ++i){
        int L,R; cin>>L>>R; --L,--R;
        cout<<st.query(L,R)<<"\n";
        st.update(L,R);
    }
}