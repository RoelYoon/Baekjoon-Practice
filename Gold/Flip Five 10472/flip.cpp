#include <iostream>
#include <queue>
#define INF ((int)1e9)
using namespace std;
void DFS(int found[], int &f, int &ans, int cnt, int s){
    if(found[s]<cnt || cnt >= ans){
        return;
    }
    found[s]=cnt;
    if(s==f){
        ans=cnt;
        return;
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            int ns = s;
            ns^=(1<<(3*i+j));
            if(i!=0){
                ns^=(1<<(3*(i-1)+j));
            }
            if(i!=2){
                ns^=(1<<(3*(i+1)+j));
            }
            if(j!=0){
                ns^=(1<<(3*i+(j-1)));
            }
            if(j!=2){
                ns^=(1<<(3*i+(j+1)));
            }
            DFS(found,f,ans,cnt+1,ns);
        }
    }
}
struct Pair{
    int d;
    int s;
    Pair(){}
    Pair(int d, int s):d(d),s(s){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin>>t;
    while(t--){
        int f = 0;
        for(int i = 0; i < 3; ++i){
            string l; cin>>l;
            for(int j = 0; j < 3; ++j){
                if(l[j]=='*')
                    f|=(1<<(3*i+j));
            }
        }
        bool found[550]{};
        queue<Pair> q;
        q.emplace(0,0);
        int ans = -1;
        while(!q.empty()){
            Pair p = q.front(); q.pop();
            if(found[p.s]) continue;
            found[p.s]=1;
            if(p.s==f){
                ans = p.d;
                break;
            }
            for(int i = 0; i < 3; ++i){
                for(int j = 0; j < 3; ++j){
                    int ns = p.s;
                    ns^=(1<<(3*i+j));
                    if(i!=0){
                        ns^=(1<<(3*(i-1)+j));
                    }
                    if(i!=2){
                        ns^=(1<<(3*(i+1)+j));
                    }
                    if(j!=0){
                        ns^=(1<<(3*i+(j-1)));
                    }
                    if(j!=2){
                        ns^=(1<<(3*i+(j+1)));
                    }
                    q.emplace(p.d+1,ns);
                }
            }
        }
        if(ans==-1){
            cout<<-1<<"\n";
            continue;
        }
        cout<<ans<<"\n";
    }
}