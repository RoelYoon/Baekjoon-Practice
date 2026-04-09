#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<string> nums;
    int n; cin>>n;
    for(int i = 0; i < n; ++i){
        string s; cin>>s;
        string num = "";
        bool reading = 0;
        for(int j = 0; j < s.size(); ++j){
            if(s[j]>='0' && s[j]<='9'){
                if(num.size()==1 && num[0]=='0') num.pop_back();
                num.push_back(s[j]);
                reading = 1;
                if(j<s.size()-1) continue;
            }
            if(!reading) continue;
            nums.push_back(num);
            num = "";   
            reading = 0;
        }
    }
    sort(nums.begin(), nums.end(), [](const string &a, const string &b) -> bool {
        if(a.size() == b.size()){
            for(int i = 0; i < a.size(); ++i){
                if(b[i] < a[i]){
                    return 0;
                }else if(a[i] < b[i]){
                    return 1;
                }
            }
        }
        return a.size() < b.size();
    });
    for(int i = 0; i < nums.size(); ++i){
        cout<<nums[i]<<"\n";
    }
}