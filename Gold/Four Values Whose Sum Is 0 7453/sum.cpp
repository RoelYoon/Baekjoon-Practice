#include <iostream>
#include <algorithm>
using namespace std;
int nums[4][4000];
int n1[4000*4000];
int n2[4000*4000];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("data.in","r",stdin);
    int n; cin>>n;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < 4; ++j)
            cin>>nums[j][i];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            n1[i*n+j] = nums[0][i]+nums[1][j];
            n2[i*n+j] = nums[2][i]+nums[3][j];
        }
    }
    sort(n1,n1 + n*n);
    sort(n2,n2 + n*n);
    long long cnt = 0;
    for(int i = 0; i < n*n; ++i){
        int lb = 0, rb = n*n-1;
        while(lb<rb){
            int mid = (lb+rb)/2;
            if(n2[mid] < -n1[i]){
                lb = mid+1;
            }else{
                rb = mid;
            }
        }
        if(n2[lb]+n1[i]==0){
            int nlb = lb;
            lb = 0, rb = n*n-1;
            while(lb<rb){
                int mid = (lb+rb+1)/2;
                if(n2[mid] <= -n1[i]){
                    lb = mid;
                }else{
                    rb = mid-1;
                }
            }
            cnt+=lb-nlb+1;
        }
    }
    cout<<cnt<<"\n";
}