#include <iostream>
#include <iomanip>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
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
    int n; cin>>n;
    vector<pt> pts;
    for(int i = 0; i < n; ++i){
        int x,y; cin>>x>>y;
        pts.emplace_back(x,y);
    }
    ll area = cross(pts.back(),pts[0]);
    for(int i = 0; i < n-1; ++i){
        area+=cross(pts[i],pts[i+1]);
    }
    cout<<fixed<<setprecision(1)<<(long double)abs(area)/2<<"\n";
}