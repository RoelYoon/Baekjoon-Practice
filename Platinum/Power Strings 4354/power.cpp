#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct KMP{
    int m;
    string P;
    vector<int> reset;
    KMP(){
        cin>>P; m=P.size(); reset.assign(m+1,0);
        int i=0,j=-1; reset[i]=j;
        while(i<m){
            while(j>=0 && P[i]!=P[j])
                j=reset[j];
            ++i,++j;
            reset[i]=j;
        }
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        KMP kmp;
        if(kmp.P==".") break;
        if(kmp.reset.back()==0){
            cout<<"1\n";
        }else{
            string P = kmp.P.substr(kmp.reset.back());
            bool mismatch=0;
            for(int i = 0,j=0; i < kmp.P.size(); i++,j=(j+1)%P.size()){
                if(kmp.P[i]!=P[j]){
                    mismatch=1;
                    break;
                }
            }
            if(mismatch){
                cout<<"1\n";
            }else{
                if(kmp.P.size()%P.size()==0){
                    cout<<kmp.P.size()/P.size()<<"\n";
                }
            }
        }
    }
}