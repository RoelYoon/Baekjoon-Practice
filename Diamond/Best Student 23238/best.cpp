#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#define MAX 100005
using namespace std;
struct Query{
    int L;
    int R;
    int id;
    Query(){}
};
struct Student{
    int id;
    int freq;
    bool operator==(const Student &rhs) const {
        return freq==rhs.freq;
    }
    Student(){}
    Student(int id, int f):id(id),freq(f){}
    struct Hash{
        size_t operator()(const Student &s)const{
            return hash<int>{}(s.freq);
        }
    };
};
class SqrtArray{
    const int n;
    const int s;
    int chunks[1005]{};
    int freq[MAX]{};
    public:
    SqrtArray(int n):n(n),s(sqrt(n)+1){}
    int query(){
        for(int i = s; i >= 0; --i){
            if(chunks[i]==0){continue;}
            for(int j = min((i+1)*s-1,n-1); j >= s*i; --j){
                if(freq[j]>0)
                    return j;
            }
        }
        return 0;
    }
    void update(int t, int u){
        freq[t]+=u;
        chunks[t/s]+=u;
    }
};
unordered_map<int,int> map;
int ids[MAX];
unordered_set<Student,Student::Hash> freqPair;
int maxSetId=0;
void expand(bool L, int p, SqrtArray&sa){
    int pFreq = map[ids[p]];
    if(pFreq>0){
        sa.update(pFreq,-1);
        freqPair.erase(Student(ids[p],pFreq));
    }
    map[ids[p]]++;
    int aFreq = map[ids[p]];
    sa.update(aFreq,1);
    freqPair.insert(Student(ids[p],aFreq));
}
void shrink(bool L, int p, SqrtArray&sa){
    int pFreq = map[ids[p]];
    if(pFreq>0){
        sa.update(pFreq,-1);
        freqPair.erase(Student(ids[p],pFreq));
    }
    map[ids[p]]--;
    int aFreq = map[ids[p]];
    sa.update(aFreq,1);
    freqPair.insert(Student(ids[p],aFreq));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    const int s = sqrt(n);
    for(int i = 0; i < n; ++i){
        cin>>ids[i];
        maxSetId=max(maxSetId,ids[i]);
        map.insert({ids[i],0});
    }
    Query qs[MAX];
    int ans[MAX];
    for(int i = 0; i < q; ++i){
        cin>>qs[i].L>>qs[i].R;
        --qs[i].L; --qs[i].R;
        qs[i].id=i;
    }
    sort(qs,qs+q,[s](Query &a, Query &b){
        if(a.L/s != b.L/s) return a.L < b.L;
        return a.L/s%2 ? a.R > b.R : a.R < b.R;
    });
    SqrtArray sa(n);
    int L = 0, R = -1;
    for(int i = 0; i < q; ++i){
        int QL = qs[i].L, QR = qs[i].R;
        while(L > QL){
            expand(1,--L,sa);
        }
        while(R < QR){
            expand(0,++R,sa);
        }
        while(L < QL){
            shrink(1,L++,sa);
        }
        while(R > QR){
            shrink(0,R--,sa);
        }
        ans[qs[i].id] = freqPair.find(Student(0,sa.query()))->id;
    }
    for(int i = 0; i < q; ++i){
        cout<<ans[i]<<"\n";
    }
}