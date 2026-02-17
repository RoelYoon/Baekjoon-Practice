#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define ll long long
using namespace std;
string s;
vector<int> nums;
ll DFS(int i, ll n1, ll n2){
    if(i == s.size()){
        return n1*n2;
    }
    ll q1 = DFS(i+1,n1*10+nums[i],n2);
    ll q2 = DFS(i+1,n1,n2*10+nums[i]);
    return max(q1,q2);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        cin>>s;
        nums.resize(s.size());
        for(int i = 0; i < s.size(); ++i){
            nums[i] = s[i]-'0';
            if(nums[i]==6){
                nums[i]=9;
            }
        }
        sort(nums.begin(),nums.end(), [](const int &a, const int &b){
            return a>b;
        });
        cout<<DFS(0,0,0)<<"\n";
    }
}