#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct KMP{
    int m;
    string p;
    vector<int> reset;
    void build(){
        m=p.size();
        reset.resize(m+1);
        int i=0,j=-1; reset[i]=j; 
        while(i<m){
            while(j>=0 && p[i]!=p[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
    }
    void next(){
        cin>>p;
        build();
    }
    KMP(){
        next();
    }
    int find(string &T){
        int i=max(0,(int)T.size()-m),j=0;
        while(i<T.size()){
            while(j>=0 && p[j]!=T[i])
                j=reset[j];
            ++i,++j;
            if(j==m && i!=T.size()){
                j=reset[j];
            }
        };
        return j;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    string ans = "";
    for(int i = 0; i < n; ++i){
        KMP s;
        string ss = (s.p.substr(s.find(ans)));
        cout<<ss;
        ans+=ss;
        if(ans.size()>1e6)
            ans=ans.substr(s.p.size()-ss.size());
    }
    cout<<"\n";
}
/*
5
abcdefghijklmnopqrstuvwxy
abcdefghijklmnopqrstuvwxy
 bcdefghijklmnopqrstuvwxy
  cdefghijklmnopqrstuvwxy
   defghijklmnopqrstuvwxyz

3
ooi ioo oioo
*/