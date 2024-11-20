#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <memory>
using namespace std;
struct Road{
    int u;
    int v;
    int w;
    int id;
    Road(){}
    Road(int u, int v, int w, int id):u(u),v(v),w(w),id(id){}
};
struct Node{
    int id;
    int dist;
    int rID;
    shared_ptr<Node> back;
    Node():back(nullptr){}
    Node(int id, int r):id(id),rID(r),back(nullptr){}
    Node(int id, int r, shared_ptr<Node> b):id(id),rID(r),back(b){}
};
unordered_map<string,int> cityID;
vector<string> city;
unordered_map<string,int> roadID;
vector<string> roadName;
vector<Road> road;
vector<vector<int>> graph(100);
int dist[100];
void print(Node path){
    cout<<"\n\nFrom                 To                   Route      Miles\n-------------------- -------------------- ---------- -----\n";
    struct AnsNode{
        int id;
        int rID;
        int dist;
        AnsNode(){}
        AnsNode(int i, int r, int d):id(i),rID(r),dist(d){}
    };
    vector<AnsNode> ans;
    while(path.back!=nullptr){
        ans.emplace_back(path.id,path.rID,path.dist);
        path=*path.back;
    }
    ans.emplace_back(path.id,path.rID,path.dist);

    for(int i = ans.size()-1; i > 0; --i){
        cout<<city[ans[i].id]<<string(21-city[ans[i].id].size(),' ')<<city[ans[i-1].id]<<string(21-city[ans[i-1].id].size(),' ')<<
        roadName[ans[i-1].rID]<<string(11-roadName[ans[i-1].rID].size(),' ')<<string(5-to_string(dist[ans[i-1].id]-dist[ans[i].id]).size(),' ')<<
        dist[ans[i-1].id]-dist[ans[i].id]<<"\n";
    }
    cout<<"                                                     -----\n"<<
    "                                          Total        "<<string(3-to_string(dist[ans[0].id]).size(),' ')<<
    dist[ans[0].id]<<"\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    string s;
    while(getline(cin,s)){
        if(s=="") break;
        stringstream ss(s);
        string inp[4];
        int i = 0;
        while(getline(ss,inp[i++],',')){}
        if(cityID.find(inp[0])==cityID.end()){
            cityID.insert({inp[0],city.size()});
            city.push_back(inp[0]);
        }
        if(cityID.find(inp[1])==cityID.end()){
            cityID.insert({inp[1],city.size()});
            city.push_back(inp[1]);
        }
        if(roadID.find(inp[2])==roadID.end()){
            roadID.insert({inp[2],roadName.size()});
            roadName.push_back(inp[2]);
        }
        graph[cityID[inp[0]]].push_back(road.size());
        road.emplace_back(cityID[inp[0]],cityID[inp[1]],stoi(inp[3]),roadID[inp[2]]);
        graph[cityID[inp[1]]].push_back(road.size());
        road.emplace_back(cityID[inp[1]],cityID[inp[0]],stoi(inp[3]),roadID[inp[2]]);
    }
    while(getline(cin,s)){
        stringstream ss(s);
        string inp[2];
        int i = 0;
        while(getline(ss,inp[i++],',')){}
        int source=cityID[inp[0]],sink=cityID[inp[1]];
        for(int i = 0; i < 100; ++i)
            dist[i]=1e9;
        dist[source]=0;
        struct City{
            int id;
            int w;
            Node path;
            City(){}
            City(int id, int w):id(id),w(w){}
            City(int id, int w, Node p):id(id),w(w),path(p){}
            bool operator<(const City &k) const {
                return w<k.w;
            }
            bool operator==(const City &k) const {
                return id==k.id;
            }
        };
        Node sourceNode(source,-1);
        set<City> pq{{source,0,sourceNode}};
        bool possible=0;
        while(!pq.empty()){
            City head = *pq.begin();
            if(head.id==sink) {possible=1; break;}
            pq.erase(pq.begin());
            for(int i = 0; i < graph[head.id].size(); ++i){
                Road &edge = road[graph[head.id][i]];
                if(dist[edge.v]>dist[edge.u]+edge.w){
                    set<City>::iterator oldPath = pq.find({edge.v,dist[edge.v]});
                    if(oldPath!=pq.end())
                        pq.erase(oldPath);
                    dist[edge.v] = dist[edge.u]+edge.w;
                    pq.insert({edge.v,dist[edge.v],Node(edge.v,edge.id,make_shared<Node>(head.path))});
                }
            }
        }
        if(possible)
            print(pq.begin()->path);
        else
            print(Node());
    }
}