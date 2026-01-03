#include <iostream>
#include <vector>
#include <unordered_set>
#define ll long long
#define MAX 4000000
using namespace std;
bool sieve[MAX+1]{};
class PrefixSum{
    vector<ll> sum;
    public:
    PrefixSum(vector<int> &arr, unordered_set<ll> &pfSet):sum(arr.size()){
        sum[0]=arr[0];
        pfSet.insert(sum[0]);
        for(int i = 1; i < arr.size(); ++i){
            sum[i]=sum[i-1]+(ll)arr[i];
            pfSet.insert(sum[i]);
        }
    }
    ll query(int L, int R){
        if(L==0) return sum[R];
        return sum[R]-sum[L-1];
    }
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    vector<int> primes;
    unordered_set<ll> pfSet;
    for(int i = 2; i <= MAX; ++i){
        if(sieve[i]) continue;
        primes.push_back(i);
        for(int j = i+i; j <= MAX; j+=i){
            sieve[j]=1;
        }
    }
    PrefixSum pSum(primes,pfSet);
    int cnt = 0;
    for(int i = 0; i < primes.size(); ++i){
        ll T = pSum.query(0,i)+(ll)n;
        if(pfSet.find(T)!=pfSet.end()){
            ++cnt;
        }
    }
    cnt+=pfSet.find(n)!=pfSet.end();
    cout<<cnt<<"\n";
}