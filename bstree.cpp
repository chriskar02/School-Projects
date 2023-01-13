#include <iostream>
using namespace std;


struct node {
    int info;
    node *left, *right;
    };
int depth = 0;
class bstree{

public:
        bstree();
    int  height();
    void insert(int x);
    int min();
    int max();
    int search(int x);
    void inorder();
    void preorder();
    void postorder();

private:
    node *root;
};

    bstree::bstree() {
    root = nullptr;
    }

    int height_aux(node *t) {
    if(t == nullptr) return 0;
    else return 1 + max(height_aux(t->left), height_aux(t->right));
    }

    int bstree::height() {
    return height_aux(root);
    }

    node *insert_aux(node *t, int x) {
    if(t == nullptr) {
        node *n = new node;
        n->info = x;
        n->left = n->right = nullptr;
        return n;
    }
    if(x < t->info) t->left = insert_aux(t->left, x);
    else t->right = insert_aux(t->right, x);
    return t;
    }

    void bstree::insert(int x) {
        root = insert_aux(root, x);
    }


    int search_aux(node *t, int x) {
        depth++;
        if(t == nullptr) return 0;
        if(x == t->info) return depth;
        else if(x < t->info) search_aux(t->left, x);
        else search_aux(t->right, x);
    }

    int bstree::search(int x) {
    return search_aux(root, x);
    }

    int min_aux(node *t) {
    if(t->left != nullptr) min_aux(t->left);
    else return t->info;
    }

    int bstree::min() {
    return min_aux(root);
    }

    int max_aux(node *t) {
    if(t->right != nullptr) max_aux(t->right);
    else return t->info;
    }

    int bstree::max() {
    return max_aux(root);
    }

    void inorder_aux(node *t) {
    if(t != nullptr) {
       inorder_aux(t->left);
       cout << t->info << " ";
       inorder_aux(t->right);
       }
    }

    void bstree::inorder() {
    inorder_aux(root);
    cout << "end" << endl;
    }

    void preorder_aux(node *t) {
    if(t != nullptr) {
        cout << t->info << " ";
        preorder_aux(t->left);
        preorder_aux(t->right);
    }
    }

    void bstree::preorder() {
    preorder_aux(root);
    cout << "end" << endl;
    }

    void postorder_aux(node *t) {
    if(t != nullptr) {
        postorder_aux(t->left);
        postorder_aux(t->right);
        cout << t->info << " ";
    }
    }

    void bstree::postorder() {
    postorder_aux(root);
    cout << "end" << endl;
    }


int main() {

  int N, M, X;
  bstree t;
  cin >> N;

  for(int i=0; i<N; i++) {
    cin >> X;
    t.insert(X);
  }

  cout << t.height() << endl;
  cout << t.min() << " " << t.max() << endl;

  cin >> M;

  for(int i=0; i<M; i++) {
    cin >> X;
    cout << t.search(X);
    if(i < M-1) cout << " ";
    else cout << endl;
    depth = 0;
  }

  t.inorder();
  t.preorder();
  t.postorder();
    }
