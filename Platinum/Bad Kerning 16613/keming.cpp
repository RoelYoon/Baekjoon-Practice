#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct KMP{
    string P;
    int m;
    vector<int> reset;
    KMP(string &s):P(s),m(s.size()),reset(m+1){
        int i = 0, j = -1;
        reset[i]=j;
        while(i<m){
            while(j>=0 && P[i]!=P[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
    }
    int match(string &T){
        int i=0, j=0, mxJ=0;
        while(i<T.size()){
            while(j>=0 && T[i]!=P[j])
                j=reset[j];
            ++i,++j;
            mxJ=max(mxJ,j);
            if(j==m)
                j=reset[j];
        }
        return mxJ;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s,p1="",p2=""; getline(cin,s);
    int n = s.size();
    for(int i = 0; i < n; ++i){
        if(i%2)
            p1+=s[i];
        else
            p2+=s[i];
    }
    KMP k1(p1),k2(p2);
    int m1=k1.match(s),m2=k2.match(s);
    //cout<<m1<<" "<<m2<<"\n";
    if(n%2){
        // m2 has end
        m2+=(m2-1)+(m2!=k2.m);
        m1+=(m1+1);
    }else{
        // m1 has end
        m1+=(m1)+1;
        m2+=m2;
    }
    //cout<<m1<<" "<<m2<<"\n";
    cout<<min(max(m1,m2),n)<<"\n";
}
/*
ENDED
AC: 4

ERROR
AC: 5

ABA
AC: 3

AABB
AC: 4

XYABAB
AC: 3

XYAABB
AC: 5

AAXYBB
AC: 4

AABC
AC: 4
*/