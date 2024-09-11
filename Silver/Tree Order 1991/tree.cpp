#include <iostream>
#include <vector>
#define MAX 100
using namespace std;
struct Node{
    Node* left;
    Node* right;
    char val;
    Node():left(nullptr),right(nullptr),val('.'){}
    Node(char v, Node *l, Node *r):left(l),right(r),val(v){}
};
void preorder(Node *head){
    if(head->val=='.') return;
    cout<<head->val;
    preorder(head->left);
    preorder(head->right);
}
void inorder(Node *head){
    if(head->val=='.') return;
    inorder(head->left);
    cout<<head->val;
    inorder(head->right);
}
void postorder(Node *head){
    if(head->val=='.') return;
    postorder(head->left);
    postorder(head->right);
    cout<<head->val;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>>n;
    Node nodes[MAX];
    for(int i = 0; i < n; ++i){
        char v, a, b;
        cin>>v>>a>>b;
        nodes[v] = Node(v,&nodes[a],&nodes[b]);
    }
    Node *root = &nodes['A'];
    preorder(root);
    cout<<"\n";
    inorder(root);
    cout<<"\n";
    postorder(root);
    cout<<"\n";
}