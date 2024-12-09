#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <bitset>
using namespace std;
int n;
int nums[15];
unordered_set<bitset<15>> found;
void printAll(int c, bitset<15> &set, string &s){
    if(found.find(set)!=found.end()) return;
    found.insert(set);
    if(c==6){
        cout<<s<<"\n";
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
    while(1){
        cin>>n;
        if(!n) break;
        found.clear();
        for(int i = 0; i < n; ++i)
            cin>>nums[i];
        sort(nums,nums+n);
        string s = "";
        bitset<15> set(0);
        printAll(0,set,s);
        cout<<"\n";
    }
}