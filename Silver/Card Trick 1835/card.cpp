#include <iostream>
using namespace std;
struct Card{
    int v;
    Card *nxt = nullptr;
    Card *prev = nullptr;
    Card(){};
    Card(int v, Card *prev, Card *nxt):v(v),prev(prev),nxt(nxt){}
};
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    Card *front = new Card(n, nullptr, nullptr);
    Card *back = front;
    for(int v = n-1; v > 0; --v){
        Card *last = new Card(v, nullptr, front);
        front->prev = last;
        front = last;
        // move back to front v times
        for(int i = 0; i < v; ++i){
            back->nxt = front;
            front->prev = back;
            front = back;
            back = back->prev;
            back->nxt = nullptr;
        }
    }
    while(front){
        cout<<front->v<<(front->nxt?" ":"\n");
        front = front->nxt;
    }
}