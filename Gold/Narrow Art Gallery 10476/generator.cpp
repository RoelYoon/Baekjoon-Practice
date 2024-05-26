#include <cstdlib> 
#include <iostream> 
#include <time.h> 
using namespace std;
int main(){
    srand(time(0));
    freopen("in","w",stdout);
    int n = 200;
    int k = 50; 
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i < n; i++){
        cout<<rand()%100<<" "<<rand()%100<<"\n";
    }
    cout<<"0 0\n";
}