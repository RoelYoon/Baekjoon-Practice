#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
typedef long long ll;
int xDir[4] = {1,0,-1,0}; 
int yDir[4] = {0,1,0,-1}; 
struct Road{
    int cost; 
    pair<int,int> coord; 
    pair<int,int> parent; 
    Road(int c, pair<int,int> cd, pair<int,int> p):cost(c),coord(cd),parent(p){}
    struct Compare{
    bool operator()(Road&a, Road&b){
        return a.cost>b.cost;
    }};
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int R,C; cin>>R>>C;
    int graph[1005][1005];
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            cin>>graph[r][c];
        }
    }
    priority_queue<Road, vector<Road>,Road::Compare> pq; 
    ll cost = graph[0][0]; 
    pq.push(Road(cost,make_pair(0,0),make_pair(0,0)));
    while(!pq.empty()){
        Road cur = pq.top();
        for(int x : xDir){
            for(int y: yDir){
                int row = cur.coord.first+y; 
                int col = cur.coord.second+x; 
                if(row>=0 && col>=0 && row<R && col<C)
                    pq.push(Road(graph[row][col],make_pair(row,col),make_pair(cur.coord.first,cur.coord.second)));
            }
        }
        
        pq.pop(); 
    }
}
