#include <iostream>
#include <string>
#include <cmath>
#include <complex>
#define ld long double
#define ll long long
#define pt complex<ll>
#define ppt complex<ld>
#define X real()
#define Y imag()
using namespace std;
ld sq(ppt p){return p.X*p.X+p.Y*p.Y;}
ld abs(ppt p){return sqrt(sq(p));}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin>>T;
    while(T--){
        int n; cin>>n;
        ppt pos(0,0);
        int dir = 0;
        for(int i = 0; i < n; ++i){
            string m; cin>>m;
            int v; cin>>v;
            if(m=="fd"){
                pos+=polar((ld)v,(ld)dir*(M_PI/180.0L));
            }else if(m=="bk"){
                pos-=polar((ld)v,(ld)dir*(M_PI/180.0L));
            }else if(m=="lt"){
                dir=(dir-v+360)%360;
            }else if(m=="rt"){
                dir=(dir+v)%360;
            }
        }
        cout<<(ll)round(abs(pos))<<"\n";
    }
}
/*
1
7
fd 100
fd 100
lt 120
fd 100
lt 120
fd 100
rt 50
*/