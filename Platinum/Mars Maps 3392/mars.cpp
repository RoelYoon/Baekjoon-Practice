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
    Point(int x, int y1, int y2, int u):x(x),y1(y1),y2(y2),u(u){}
};
class SegmentTree{
    #define LC(p) (2*p+1)
    #define RC(p) (2*p+2)
    int n;
    vector<int> on;
    vector<int> freq;
    vector<bool> lazy;
    vector<int> upd;
    inline bool outBounds(int L, int R, int QL, int QR){
        return R < QL || L >QR;
    }
    inline bool inBounds(int L, int R, int QL, int QR){
        return L>=QL && R<=QR;
    }
    int query(int p, int L, int R, int QL, int QR){
        if(outBounds(L,R,QL,QR)){
            return 0;
        }
        if(inBounds(L,R,QL,QR)){
            return on[p];
        }
        int mid = (L+R)/2;
        return query(LC(p),L,mid,QL,QR) + query(RC(p),mid+1,R,QL,QR);
    }
    void update(int p, int L, int R, int QL, int QR, int u){
        if(outBounds(L,R,QL,QR)){
            return;
        }
        if(inBounds(L,R,QL,QR)){
            freq[p]+=u;
        }else{
            int mid = (L+R)/2;
            update(LC(p),L,mid,QL,QR,u);
            update(RC(p),mid+1,R,QL,QR,u);
        }
        if(freq[p]>0){
            on[p]=(R-L+1);
        }else if(L==R){
            on[p]=0;
        }else{
            on[p]=on[LC(p)]+on[RC(p)];
        }
    }
    public:
    SegmentTree(int n):n(n),on(4*n),freq(4*n),lazy(4*n),upd(4*n){}
    int query(){
        return query(0,0,n-1,0,n-1);
    }
    void update(int L, int R,int u){
        update(0,0,n-1,L,R,u);
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<Point> points;
    int minY = 1e9, maxY = 0;
    for(int i = 0; i < n; ++i){
        int x1,x2,y1,y2; cin>>x1>>y1>>x2>>y2;
        points.emplace_back(x1,y1,y2,1);
        points.emplace_back(x2,y1,y2,-1);
        minY=min(minY,min(y1,y2));
        maxY=max(maxY,max(y1,y2));
    }
    sort(points.begin(),points.end(),[](const Point &a, const Point &b){return a.x<b.x;});
    SegmentTree st(maxY-minY);
    ll A = 0;
    for(int i = 0; i < points.size()-1; ++i){
        st.update(points[i].y1-minY,points[i].y2-minY-1,points[i].u);
        A+=(st.query())*(points[i+1].x-points[i].x);
    }
    cout<<A<<"\n";
}