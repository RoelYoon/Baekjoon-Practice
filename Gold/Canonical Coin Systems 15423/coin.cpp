#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n;
int mx; 
int Greedy(vector<int> &coins, int sum){
    int i = n-1;
    int cnt = 0;
    while(sum>0){
        int m = sum/coins[i];
        sum-=coins[i]*m;
        i--;
        cnt+=m;
    }
    return cnt;
}
bool BFS(vector<int> &coins){
    struct qElement{
        int sum;
        int num; 
        qElement(int s, int n):sum(s),num(n){}
    };
    queue<qElement> q; q.push(qElement(0,0));
    bool *mem = new bool[3000000]; mem[0]=1; mem[mx]=1;
    while(!q.empty()){
        int num = q.front().num, sum=q.front().sum; q.pop();
        if(Greedy(coins,sum)>num)
            return false;
        for(int i = 0; i < n; i++){
            int nxt = sum+coins[i];
            if(mem[nxt] || nxt>=mx)
                continue;
            mem[nxt]=true;
            q.emplace(nxt,num+1);
        }
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    vector<int> coins(n);
    for(int i = 0; i < n; i++)
        cin>>coins[i];
    mx = coins[n-2]+coins[n-1];
    cout<<(BFS(coins)?"canonical":"non-canonical")<<"\n";
}