#include <iostream>
using namespace std;
struct Node{
    int v;
    Node* left;
    Node* right;
    Node():left(nullptr),right(nullptr){}
    Node(int v):v(v),left(nullptr),right(nullptr){}
};
class BST{
    void insert(int x, Node*& cur){
        if(cur==nullptr){
            cur = new Node(x);
            return;
        }
        if(x<cur->v){
            insert(x,cur->left);
        }else{
            insert(x,cur->right);
        }
    }
    public:
    Node* head;
    BST():head(nullptr){}
    void insert(int x){
        insert(x,head);
    }
};
void DFS(Node *cur){
    if(cur==nullptr) return;
    DFS(cur->left);
    DFS(cur->right);
    cout<<cur->v<<"\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x;
    BST bst;
    while(cin>>x)
        bst.insert(x);
    DFS(bst.head);
}