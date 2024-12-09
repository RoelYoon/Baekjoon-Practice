#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <bitset>
using namespace std;
int m,n;
int nums[15];
unordered_set<bitset<15>> found;
unordered_set<string> sFound;
void printAll(int c, bitset<15> &set, string &s){
    if(found.find(set)!=found.end()) return;
    found.insert(set);
    if(c==m){
        if(sFound.find(s)!=sFound.end()) return;
        cout<<s<<"\n";
        sFound.insert(s);
        return;
    }
    for(int i = 0; i < n; ++i){
        if(!set[i]){
            set[i]=1;
            string ns = to_string(nums[i])+" ";
            s+=ns;
            printAll(c+1,set,s);
            for(int j = 0; j < ns.size(); ++j)
                s.pop_back();
            set[i]=0;
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i = 0; i < n; ++i)
        cin>>nums[i];
    sort(nums,nums+n);
    string s = "";
    bitset<15> set(0);
    printAll(0,set,s);
}