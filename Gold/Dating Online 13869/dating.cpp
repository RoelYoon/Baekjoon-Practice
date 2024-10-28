#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long double ld;
typedef complex<ld> Point;
#define X real()
#define Y imag()
inline ld cross(Point &a, Point &b){
    return (conj(a)*b).Y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    ld au = (M_PI*2)/n;
    vector<int> rs(n);
    for(int i = 0; i < n; ++i)
        cin>>rs[i];
    sort(rs.begin(),rs.end());
    vector<Point> points;
    double area = 0;
    if(n%2){
        int ai = 0;
        for(int i = 1; i < n; i+=2)
            points.emplace_back(polar((ld)rs[i],au*(ai++)));
        for(int i = n-1; i >= 0; i-=2)
            points.emplace_back(polar((ld)rs[i],au*(ai++)));
    }else{
        int ai = 0;
        for(int i = 1; i < n; i+=2)
            points.emplace_back(polar((ld)rs[i],au*(ai++)));
        for(int i = n-2; i >= 0; i-=2)
            points.emplace_back(polar((ld)rs[i],au*(ai++)));        
    }
    area=cross(points[n-1],points[0]);
    for(int i = 0; i < n-1; ++i){
        area+=cross(points[i],points[i+1]);
    }
    cout<<setprecision(3)<<fixed<<abs(area)/2<<"\n";
}