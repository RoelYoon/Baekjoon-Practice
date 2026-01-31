#include <iostream>
using namespace std;
struct State{
    int a;
    int b;
    char c;
    State(){}
    State(int a, int b, char c):a(a),b(b),c(c){}
    bool operator==(const State &k) const {
        return a==k.a && b==k.b;
    }
};
State P[1000][1000]{};
int DP[1000][1000]{};
string a,b;
void printAns(State head, int &length){
    ++length;
    if(P[head.a][head.b]==head){
        if(P[head.a][head.b].c!='x') cout<<P[head.a][head.b].c;
        return;
    }
    printAns(P[head.a][head.b],length);
    if(P[head.a][head.b].c!='x') cout<<P[head.a][head.b].c;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>a>>b;
    State headState(-1,-1,'x');
    int mxSt = -1;
    for(int ai = 0; ai < a.size(); ++ai){
        for(int bi = 0; bi < b.size(); ++bi){
            int mx = -1;
            if(ai != 0){
                if(DP[ai-1][bi]>mx){
                    mx = DP[ai-1][bi];
                    P[ai][bi]=State(ai-1,bi,'x');
                }
            }
            if(bi != 0){
                if(DP[ai][bi-1]>mx){
                    mx = DP[ai][bi-1];
                    P[ai][bi]=State(ai,bi-1,'x');
                }
            }
            if(ai!=0 && bi!=0 && a[ai]==b[bi]){
                if(DP[ai-1][bi-1]+1 > mx){
                    mx = DP[ai-1][bi-1]+1;
                    P[ai][bi]=State(ai-1,bi-1,a[ai]);
                    if(mx>mxSt)
                        headState = P[ai][bi];
                }
            }
            if((a[ai]==b[bi]) > mx){
                mx = a[ai]==b[bi];
                P[ai][bi]=State(ai,bi,a[ai]==b[bi]?a[ai]:'x');
                if(mx>mxSt)
                    headState = P[ai][bi];
            }
            DP[ai][bi]=mx;
            mxSt = max(mxSt,DP[ai][bi]);
        }
    }
    cout<<DP[a.size()-1][b.size()-1]<<"\n";
    if(mxSt!=0){
        int length = 0;
        printAns(headState,length);
        if(length>1 && headState.c!='x') cout<<headState.c;
        cout<<"\n";
    }
}