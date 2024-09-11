#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<string> answers;
void DFS(vector<string> &id2Name, vector<bool> &visited, vector<vector<int>> &graph, int head){
    for(int i = 0; i < graph[head].size(); ++i){
        if(!visited[graph[head][i]]){
            visited[graph[head][i]]=1;
            answers.push_back(id2Name[graph[head][i]]);
            DFS(id2Name,visited,graph,graph[head][i]);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    unordered_map<string, int> name2id;
    vector<string> id2Name(2*n+5);
    vector<vector<int>> graph(2*n+5);
    int id = 0;
    for(int i = 0; i < n; ++i){
        string a, is, b;
        cin>>a>>is>>b;
        if(name2id.find(a)==name2id.end()){
            name2id.insert({a,id});
            id2Name[id++] = a;
        }
        if(name2id.find(b)==name2id.end()){
            name2id.insert({b,id});
            id2Name[id++] = b;
        }
        int aID = name2id.find(a)->second;
        graph[aID].push_back(name2id.find(b)->second);
    }
    if(name2id.find("Baba")==name2id.end()){return 0;}
    vector<bool> visited(n,false); visited[name2id.find("Baba")->second]=1;
    DFS(id2Name,visited,graph,name2id.find("Baba")->second);
    sort(answers.begin(),answers.end());
    for(int i = 0; i < answers.size(); ++i)
        cout<<answers[i]<<"\n";
}
/*
4
Rabbit is Carrot
Baba is Cat
Cat is Rabbit
Carrot is Baba
*/