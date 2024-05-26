#include <iostream>
#include <vector> 
#include <queue> 
#include <memory>
#include <utility>
using namespace std;
int correctHay = 0;
int orderCount = 0;
int source = 0;
int initial = 0; 
bool found = false;
queue<pair<int, int> > orderQ;
struct node{
    int h = 0;
    vector<int> connections;
};
void DFSupdate(vector<vector<int> > &paths, vector<shared_ptr<node> > &graph, vector<bool> &visited, int &updateAmount, int head){
    if(visited[head]){return;}
    visited[head]=true;
    if(head==source){
        found=true; 
        initial=source; 
        if(paths[source][initial]!=0){
            orderCount++;
            orderQ.push(make_pair(head,initial));
        }
        return;
    }
    for(shared_ptr<node> barn : graph){
        for(int connection : barn->connections){
            if(found){break;}
            DFSupdate(paths,graph,visited,updateAmount,connection);
        }
    }
    if(found){
        if(paths[head][initial]!=0){
            orderCount++;
            orderQ.push(make_pair(head,initial));
        }
        paths[head][initial]+=updateAmount;
        initial=head;
    }
}
void resourceCall(vector<vector<int> > &paths, vector<shared_ptr<node> > &graph, vector<bool> &visited, queue<pair<int, int> > &BFSq, int &request){
    if(request <= 0 || BFSq.empty()){
        return;
    }
    pair<int, int> temp = BFSq.front();
    int head = temp.first;
    BFSq.pop();
    visited[head]=true;
    shared_ptr<node> cur = graph[head];
    if(cur->h > correctHay){
        int donation=0;
        if(cur->h-correctHay >= request){
            donation = request;
            cur->h -= request;
        }else{
            donation = cur->h - correctHay;
            cur->h = correctHay;
        }
        vector<bool> visited(graph.size(),false);
        found=false;
        initial=head;
        DFSupdate(paths,graph,visited,donation,head);
    }
    if(request>0){
        for(int connection : (*graph[head]).connections){
            if(!visited[connection]){
                BFSq.push(make_pair(connection,head));
            }
        }
        resourceCall(paths, graph, visited, BFSq, request);  
    }
}
int main(){
    /*
    ios::sync_with_stdio(false);
    cin.tie(0);
    */
    int n; 
    cin>>n;
    vector<vector<int> > pathCounts(n,vector<int>(n,0));
    vector<shared_ptr<node> > graph(n);
    for(int i = 0; i < n; i++){
        shared_ptr<node> temp = shared_ptr<node>(new node);
        cin>>temp->h;
        correctHay+=temp->h;
        graph[i]=temp;
    }
    correctHay/=n;
    for(int i = 0; i < n-1; i++){
        int a,b;
        cin>>a>>b;
        graph[a-1]->connections.push_back(b-1);
        graph[b-1]->connections.push_back(a-1);
    }
    for(int i = 0; i < n; i++){
        node cur = *graph[i];
        if(cur.h < correctHay){
            queue<pair<int,int> > BFSq;
            int request = correctHay-cur.h;
            BFSq.push(make_pair(i,i));
            source = i; 
            vector<bool> visited(n,false);
            resourceCall(pathCounts,graph, visited, BFSq,request);
        }
    }
    cout<<orderCount<<"\n";
    while(!orderQ.empty()){
        pair<int,int> step = orderQ.front();
        orderQ.pop();
        cout<<step.first+1<<" "<<step.second+1<<" "<<pathCounts[step.first][step.second]<<"\n";
    }
    for(int i = 0; i < pathCounts.size(); i++){
        for(int j = 0; j < pathCounts[0].size(); j++){
            cout<<pathCounts[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0; 
}
/*
for any node with less than the required haybale, make a resource call

the resource call will run a BFS on the tree until it finds a node with more haybales than the required amount

while backtracking on BFS, record the amount being moved between paths in a matrix
4
2 1 4 5
1 2
2 3
2 4

3
3 2 1
4 2 2
2 1 1
*/