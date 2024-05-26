#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;
unordered_set<string> dictionary; 
void generate(string &s, int used,unordered_set<string> &seen,unordered_map<char,int> &counts, string perm){
    if(seen.find(perm)!=seen.end()){return;}
    if(dictionary.find(perm)==dictionary.end()){
        if(perm.size()==1 || perm.size()==2 || perm.size()==3){
            return; 
        }
    }else if(perm.size() > 3){
        bool counted[300]{};
        for(int i =0; i < 9; i++){
            if(used & (1<<i) && !counted[(int)s[i]]){
                counts[s[i]]++;
                counted[(int)s[i]]=1;
            }
        }
    }
    seen.insert({perm});
    for(int i = 0; i < 9; i++){
        if(!(used & (1<<i))){
            int copy = used;
            used = used | (1<<i);
            generate(s,used,seen,counts,perm+s[i]);
            used = copy;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    while(1){
        string s; 
        cin>>s; 
        if(s=="-")
            break;
        dictionary.insert({s});
        dictionary.insert({s.substr(0,1)}); 
        dictionary.insert({s.substr(0,2)});
        dictionary.insert({s.substr(0,3)});
    }
    while(1){
        string grid; 
        unordered_set<string> seen;
        unordered_map<char, int> counts; 
        cin>>grid; 
        if(grid=="#")
            break;
        for(int i = 0; i < 9; i++){
            counts.insert({grid[i],0});
        }
        string minCenters="", maxCenters="";
        int minCount=1000000000, maxCount=-1;
        int used = 0;
        string perm = "";
        generate(grid,used,seen,counts,perm); 
        for(unordered_map<char,int>::iterator it = counts.begin(); it!=counts.end(); it++){
            if(it->second < minCount){
                minCount = it->second;
                minCenters = it->first;
            }else if(it->second == minCount){
                minCenters += it->first;
            }
            if(it->second > maxCount){
                maxCount = it->second;
                maxCenters = it->first;
            }else if(it->second == maxCount){
                maxCenters += it->first;
            }
        }
        sort(minCenters.begin(),minCenters.end());
        sort(maxCenters.begin(),maxCenters.end());
        std::cout<<minCenters<<" "<<minCount<<" "<<maxCenters<<" "<<maxCount<<"\n";
    }
}