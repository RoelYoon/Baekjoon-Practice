#include <iostream>
#include <vector>
#define MAX 100005
using namespace std;
int gcd(int a, int b){
    return b==0?a:gcd(b,a%b);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    while(cin>>n){
        if(n==0) break;
        int data[MAX];
        bool fd[MAX]{};
        for(int i = 0; i < n; ++i){
            cin>>data[i];
            fd[data[i]]=1;
        }
        int cnt = 0;
        for(int i = 1; i <= 100; ++i){
            if(fd[i]){cnt++;continue;}
            int g = data[0];
            for(int j = 1; j < n; ++j){
                g=gcd(g,data[j]);
                if(g==i){++cnt; fd[i]=1; break;}
                else if(g%i!=0){
                    g=data[j];
                }
            }
        }
        cout<<cnt<<"\n";
    }
}