#include <iostream>
#include <iomanip>
#include <cmath>
#define ld long double
using namespace std;
const ld PI = acos(-1);
ld ans(ld &x1,ld &y1,ld &r1,ld &x2,ld &y2,ld &r2){
    ld d = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    //no overlap
    if(d>r1+r2)
        return 0;
    //complete overlap
    if((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)<=(r1-r2)*(r1-r2))
        return PI*r2*r2;
    ld bct = (r1*r1+d*d-r2*r2)/(2*r1*d);
    ld bt = acos(bct);
    ld bst = sin(bt);
    ld dH = 2*r1*bst;
    ld sct = (r2*r2+d*d-r1*r1)/(2*r2*d);
    ld st = acos(sct);
    return (r1*r1*bt)+(r2*r2*st)-(dH*d/2);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ld x1,y1,x2,y2,r1,r2;
    cin>>x1>>y1>>r1>>x2>>y2>>r2;
    if(r1<r2){
        ld c=x1,x1=x2,x2=c;
        c=y1,y1=y2,y2=c;
        c=r1,r1=r2,r2=c;
    }
    cout<<fixed<<setprecision(3)<<ans(x1,y1,r1,x2,y2,r2)<<"\n";
}
