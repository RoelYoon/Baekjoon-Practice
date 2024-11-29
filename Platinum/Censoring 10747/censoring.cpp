#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct KMP{
    int m;
    string P;
    vector<int> reset;
    KMP(){
        getline(cin,P);
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
            int i,j;
            Pair(){}
            Pair(int i, int j):i(i),j(j){}
        };
        vector<Pair> ans;
        string ansS;
        int i=0,j=0;
        while(i<T.size()){
            ans.push_back({i,j});
            ansS.push_back(T[i]);
            while(j>=0 && T[i]!=P[j])
                j=reset[j];
            ++i,++j;
            ans[ans.size()-1].j=j;
            if(j==m){
                ans.erase(ans.end()-m,ans.end());
                ansS.erase(ansS.end()-m,ansS.end());
                j=ans[ans.size()-1].j;
            }
        }
        cout<<ansS<<"\n";
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    getline(cin,s);
    KMP kmp;
    kmp.search(s);
}