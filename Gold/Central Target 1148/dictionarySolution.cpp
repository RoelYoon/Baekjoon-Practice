#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<string> words; 
    vector<array<int,100>> rolls,counts;
    while(1){
        string s; cin>>s;
        if(s=="-")
            break;
        words.push_back(s);
    }
    while(1){
        string s; cin>>s;
        if(s=="#")
            break;
        array<int,100> roll{};
        for(int i = 0; i < 9; i++)
            roll[s[i]]++;
        rolls.push_back(roll);
        counts.push_back(array<int,100>{});
    }
    for(int i = 0; i < words.size(); i++){
        for(int j = 0; j < rolls.size(); j++){
            array<int,100> arrayCopy = rolls[j];
            bool constructable = true;
            for(int k = 0; k < words[i].size(); k++){
                if(arrayCopy[words[i][k]]-- <= 0){
                    constructable=0;
                }
            }
            if(constructable){
                array<bool,100> counted{};
                for(int k = 0; k < words[i].size(); k++){
                    if(!counted[words[i][k]]){
                        counts[j][words[i][k]]++;
                        counted[words[i][k]]=1;
                    }
                }
            }
        }
    }
    for(int i = 0; i < counts.size(); i++){
        string minCenters="", maxCenters="";
        int minCount=1000000000, maxCount=-1;
        for(int j = 65; j <= 90; j++){
            if(rolls[i][j]==0){continue;}
            if(counts[i][j] < minCount){
                minCount = counts[i][j];
                minCenters = (char)j;
            }else if(counts[i][j] == minCount){
                minCenters += (char)j;
            }
            if(counts[i][j] > maxCount){
                maxCount = counts[i][j];
                maxCenters = (char)j;
            }else if(counts[i][j] == maxCount){
                maxCenters += (char)j;
            }
            sort(minCenters.begin(),minCenters.end());
            sort(maxCenters.begin(),maxCenters.end());
        }cout<<minCenters<<" "<<minCount<<" "<<maxCenters<<" "<<maxCount<<"\n";
    }
}