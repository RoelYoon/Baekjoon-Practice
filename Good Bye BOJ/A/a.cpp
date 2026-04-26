#include <iostream>
#include <string>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); 
    int n; cin>>n;
    for(int r = 0; r < 2*n; ++r){
        for(int i = 0; i < (2*n-r-1); ++i){
            cout<<" ";
        }
        cout<<"*";
        if(r/n == 0){
            for(int i = 0; i < n; ++i){
                cout<<" ";
            }
        }else{
            for(int i = 0; i < n+(r-n)*2+1; ++i){
                cout<<" ";
            }
        }
        cout<<"*";
        if(r/n == 0){
            for(int i = 0; i < r*2+1; ++i){
                cout<<" ";
            }
        }else{
            for(int i = 0; i < 2*n-1 - (r-n)*2; ++i){
                cout<<" ";
            }
        }
        cout<<"*";
        if(r/n == 0){
            for(int i = 0; i < n-1-r; ++i){
                cout<<" ";
            }
        }else{
            for(int i = 0; i < r-n; ++i){
                cout<<" ";
            }
        }
        cout<<"\n";
    }
}