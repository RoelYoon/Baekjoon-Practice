#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <utility>
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
    bool operator<(const Student &rhs) const {
        if(freq==rhs.freq){return id<rhs.id;}
        return freq < rhs.freq;
    }
    Student(){}
    Student(int id, int f):id(id),freq(f){}
};
unordered_map<int,int> freq;
set<Student> bst;
int ids[MAX];
void expand(bool L, int p){
    bst.erase(Student(ids[p],freq[ids[p]]));
    freq[ids[p]]++;
    bst.insert(Student(ids[p],freq[ids[p]]));
}
void shrink(bool L, int p){
    bst.erase(Student(ids[p],freq[ids[p]]));
    freq[ids[p]]--;
    bst.insert(Student(ids[p],freq[ids[p]]));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n,q; cin>>n>>q;
    const int s = sqrt(n);
    for(int i = 0; i < n; ++i){
        cin>>ids[i];
        freq.insert({ids[i],0});
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
    int L = 0, R = -1;
    for(int i = 0; i < q; ++i){
        int QL = qs[i].L, QR = qs[i].R;
        while(L > QL){
            expand(1,--L);
        }
        while(R < QR){
            expand(0,++R);
        }
        while(L < QL){
            shrink(1,L++);
        }
        while(R > QR){
            shrink(0,R--);
        }
        ans[qs[i].id] = bst.rbegin()->id;
    }
    for(int i = 0; i < q; ++i){
        cout<<ans[i]<<"\n";
    }
}