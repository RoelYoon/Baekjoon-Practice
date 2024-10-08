#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
struct Point{
    int x;
    int y1;
    int y2;
    int u;
    Point(){}
    void set(int xi, int y1i, int y2i, int ui){
        x=xi;
        y1=y1i;
        y2=y2i;
        u=ui;
    }
};
Point points[400000];
struct Node{
    int on;
    int freq;
    Node *left=nullptr;
    Node *right=nullptr;
    Node(){}
    Node(int o, int f):on(o),freq(f){}
    ~Node(){
        if(left) delete left;
        if(right) delete right;
    }
};
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    Node root;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L >QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int query(Node *p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return p->on;
        }
        int mid = (L+R)/2;
        if(!p->left){
            p->left=new Node(0,0);
        }
        if(!p->right){
            p->right=new Node(0,0);
        }
        return query(p->left,L,mid,QL,QR) + query(p->right,mid+1,R,QL,QR);
    }
    void update(Node* p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            p->freq+=u;
        }else{
            int mid = (L+R)/2;
            if(!p->left){
                p->left=new Node(0,0);
            }
            if(!p->right){
                p->right=new Node(0,0);
            }
            update(p->left,L,mid,QL,QR,u);
            update(p->right,mid+1,R,QL,QR,u);
        }
        if(p->freq>0){
            p->on=(R-L+1);
        }else if(L==R){
            p->on=0;
        }else{
            if(!p->left){
                p->left=new Node(0,0);
            }
            if(!p->right){
                p->right=new Node(0,0);
            }
            p->on=p->left->on+p->right->on;
        }
    }
    public:
    SegmentTree(int n):n(n),root(0,0){}
    int query(){
        return query(&root,0,n-1,0,n-1);
    }
    void update(int L, int R,int u){
        update(&root,0,n-1,L,R,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    int minY = 1e9, maxY = 0;
    for(int i = 0; i < n; ++i){
        int x1,x2,y1,y2; cin>>x1>>x2>>y1>>y2;
        points[i].set(x1,y1,y2,1);
        points[i+n].set(x2,y1,y2,-1);
        minY=min(minY,min(y1,y2));
        maxY=max(maxY,max(y1,y2));
    }
    sort(points,points+2*n,[](const Point &a, const Point &b){return a.x<b.x;});
    SegmentTree st(maxY-minY);
    ll A = 0;
    for(int i = 0; i < 2*n-1; ++i){
        st.update(points[i].y1-minY,points[i].y2-minY-1,points[i].u);
        A+=(ll)st.query()*(ll)(points[i+1].x-points[i].x);
    }
    cout<<A<<"\n";
}