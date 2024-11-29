#include <iostream>
#include <vector>
using namespace std;
class KMP{
    private:
    int m;
    string P;
    vector<int> reset; //if matchmatch at i, continue from reset[i]
    public:
    KMP(){
        getline(cin,P);
        m=P.size();
        reset.assign(m+1,0);
        int i=0,j=-1;
        reset[i]=j;
        while(i<m){
            while(j>=0 && P[i]!=P[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
    }
    void search(string &T,vector<int> &pos){
        int i=0,j=0;
        while(i<T.size()){
            while(j>=0 && P[j]!=T[i])
                j=reset[j];
            ++i,++j;
            if(j==m){
                pos.push_back(i-j+1);
                j=reset[j];
            }
        }
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string T; getline(cin,T);
    KMP kmp;
    vector<int> pos;
    kmp.search(T,pos);
    cout<<pos.size()<<"\n";
    for(int i = 0; i < pos.size(); ++i){
        cout<<pos[i]<<" ";
    }
    cout<<(pos.empty()?"":"\n");
}