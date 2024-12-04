#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class KMP{
    private:
    int m;
    vector<int> p;
    vector<int> reset;
    public:
    KMP(string &word, unordered_map<char,int> &map){
        m=word.size();
        reset.resize(m+1);
        p.resize(m);
        int i=0,j=-1; reset[i]=j; 
        while(i<m){
            while(j>=0 && word[i]!=word[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
        for(int i = 0; i < m; ++i)
            p[i]=map[word[i]];
    }
    int find(vector<int> &T,const int a, int k){
        if(T.size()<m) return 0;
        int i=0,j=0,cnt=0;
        while(i<T.size()){
            while(j>=0 && (p[j]+k)%a!=T[i])
                j=reset[j];
            ++i,++j;
            if(j==m){
                ++cnt;
                j=reset[j];
            }
        };
        return cnt;
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        unordered_map<char,int> map;
        string alphabet,word,code;
        cin>>alphabet>>word>>code;
        for(int i = 0; i < alphabet.size(); ++i)
            map[alphabet[i]]=i;
        KMP kmp(word,map);
        vector<int> numCode(code.size());
        for(int i = 0; i < code.size(); ++i)
            numCode[i]=map[code[i]];
        vector<int> ans;
        for(int k = 0; k < alphabet.size(); ++k){
            if(kmp.find(numCode,alphabet.size(),k)==1){
                ans.push_back(k);
            }
        }
        if(ans.empty()){
            cout<<"no solution\n";
        }else{
            if(ans.size()==1){
                cout<<"unique: ";
            }else{
                cout<<"ambiguous: ";
            }
            for(int i = 0; i < ans.size(); ++i){
                cout<<ans[i]<<" ";
            }cout<<"\n";
        }
    }
}
/*
1
ABC
ABC
ABCBCAABC
*/