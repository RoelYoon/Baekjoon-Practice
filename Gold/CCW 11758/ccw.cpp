#include <iostream>
#include <complex>
#include <cmath>
#define ll long long
#define pt complex<ll>
#define X real()
#define Y imag()
using namespace std;
ll cross(pt a, pt b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x1,x2,x3,y1,y2,y3;
    cin>>x1>>y1>>x2>>y2>>x3>>y3;
    pt p1(x1,y1),p2(x2,y2),p3(x3,y3);
    ll c = cross(p2-p1,p3-p2);
    cout<<(c>0?1:(c<0?-1:0))<<"\n";
}
