#include <iostream>
#include <iomanip>
#include <vector>
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
    int n; cin>>n;
    long double area = 0;
    for(int i = 0; i < n; ++i){
        int s; cin>>s;
        vector<pt> points;
        for(int j = 0; j < s; ++j){
            int x,y; cin>>x>>y;
            points.emplace_back(x,y);
        }
        ll a = cross(points.back(),points[0]);
        for(int j = 0; j < s-1; ++j){
            a+=cross(points[j],points[j+1]);
        }
        area+=(double)abs(a)/2;
    }
    cout<<(ll)area<<"\n";
}
