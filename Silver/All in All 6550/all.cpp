#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string a,b;
    while(cin>>a>>b){
        if(b.size()<a.size()){
            cout<<"No\n";
            continue;
        }
        int j = 0;
        for(int i = 0; i < b.size(); ++i){
            j+=a[j]==b[i];
            if(j>=a.size()) break;
        }
        cout<<(j>=a.size()?"Yes\n":"No\n");
    }
}
