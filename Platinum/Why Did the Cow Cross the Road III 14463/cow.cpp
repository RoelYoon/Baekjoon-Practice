#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
struct Query{
    int L=-1,R;
    Query(){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    const int s = sqrt(n);
    vector<int> nums(2*n);
    vector<Query> queries(n);
    for(int i = 0; i < 2*n; ++i){
        cin>>nums[i]; --nums[i];
        if(queries[nums[i]].L<0){
            queries[nums[i]].L=i;
        }else{
            queries[nums[i]].R=i;
        }
    }
    sort(queries.begin(),queries.end(),[s](const Query &a, const Query &b){
        if(a.L/s == b.L/s) return (a.L/s%2 ? a.R>b.R : a.R<b.R);
        return a.L<b.L;
    });
    int ans = 0,prevCnt=0;
    int L=0, R=-1;
    vector<int> freq(n);
    for(int i = 0; i < n; ++i){
        int QL=queries[i].L, QR=queries[i].R, cnt=prevCnt;
        //expand
        while(R<QR){
            ++freq[nums[++R]];
            cnt+=(freq[nums[R]]==1?1:-1);
        }
        while(L>QL){
            ++freq[nums[--L]];
            cnt+=(freq[nums[L]]==1?1:-1);
        }
        //shrink
        while(R>QR){
            --freq[nums[R--]];
            cnt+=(freq[nums[R+1]]==1?1:-1);
        }
        while(L<QL){
            --freq[nums[L++]];
            cnt+=(freq[nums[L-1]]==1?1:-1);
        }
        ans+=cnt;
        prevCnt=cnt;
    }
    cout<<ans/2<<"\n";
}