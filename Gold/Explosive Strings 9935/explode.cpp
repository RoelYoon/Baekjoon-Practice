#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct KMP{
    int m;
    string P;
    vector<int> reset;
    KMP(){
        cin>>P; cin.ignore();
        m=P.size();
        reset.resize(m+1);
        int i=0,j=-1; reset[i]=j;
        while(i<m){
            while(j>=0 && P[i]!=P[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
    }
    void search(string &T){
        struct Pair{
            char c;
            int i;
            int j;
            Pair(){}
            Pair(char c, int i):c(c),i(i){}
            Pair(char c, int i, int j):c(c),i(i),j(j){}
        };
        vector<Pair> ans;
        int i=0,j=0;
        while(i<T.size()){
            ans.push_back({T[i],i,j});
            while(j>=0 && T[i]!=P[j])
                j=reset[j];
            ++i,++j;
            ans.back().j=j;
            if(j==m){
                ans.erase(ans.end()-m,ans.end());
                j=ans.back().j;
            }
        }
        for(int k = 0; k < ans.size(); ++k)
            cout<<ans[k].c;
        if(ans.empty())
            cout<<"FRULA";
        cout<<"\n";
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; getline(cin,s);
    KMP kmp;
    kmp.search(s);
}