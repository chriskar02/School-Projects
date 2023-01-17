#include <iostream>
using namespace std;

class lexicon {
public:
 lexicon(){
     root = nullptr;
 }

 ~lexicon(){
     purge(root); root = nullptr;
     }

 void insert(const string &s){
        root = insert_aux(root,s);
    }

 int lookup(const string &s) const{
     node *q = root;
     if(q==nullptr) return 0;
     if(q->word==s) return q->times;
     while(q!=nullptr && q->word != s){
         if(q->word < s){
             if(q->right==nullptr) return 0;
             q = q->right;
        } else {
        if(q->left==nullptr) return 0;
        q = q->left;
        }
     }
     if(q==nullptr) return 0;
     return q->times;
 }

 int depth(const string &s) const{
     node *q = root;
     if(q==nullptr) return -1;
     if(q->word==s) return 0;
     int place=0;
     while(q!=nullptr && q->word != s){
         place++;
         if(q->word < s){
             if(q->right==nullptr) return -1;
             q = q->right;
         } else {
             if(q->left==nullptr) return -1;
             q = q->left;
         }
     }
     if(q==nullptr) return -1;
     return place;
 }

 void replace(const string &s1, const string &s2){
     node *q,*p;
     if(lookup(s1) != 0){
     q = place(s1);}
     else{return;}
     if(lookup(s2)!=0){
         p=place(s2);
         p->times+=q->times;
     }else{
         root=insert_aux(root,s2);
         p=place(s2);
         p->times+=q->times-1;
     }
     if(q->left == nullptr && q->right == nullptr){
         if(q->parent->word>q->word) {
         q->parent->left = nullptr;
         delete q;
         return;
         }
         q->parent->right= nullptr;
         delete q;
         return;
     }
     if(q->left == nullptr && q->right != nullptr){
         if(q->parent == nullptr){
             root=root->right;
             root->parent = nullptr;
             delete q;
             return;
         }else{
             if(q->word<q->parent->word){
                 q->parent->left=q->right;
                 q->right->parent=q->parent;
                 delete q;
                 return;}
             else{
                 q->parent->right=q->right;
                 q->right->parent=q->parent;
                 delete q;
                 return;}}
     }
     if(q->left != nullptr && q->right == nullptr){
         if(q->parent == nullptr){
             root=root->left;
             root->parent = nullptr;
             delete q;
             return;
         } else{
             if(q->word<q->parent->word){
                 q->parent->left=q->left;
                 q->left->parent=q->parent;
                 delete q;
                 return;
             } else{
                 q->parent->right=q->left;
                 q->left->parent=q->parent;
                 delete q;
                 return;
                 }
         }
     }
     if(q->left != nullptr && q->right != nullptr){
         node *need1,*need2;
         need1 = search(q->left);
         need2 = q->right;
         if(need1!=q->left){
             need1->parent=q->parent;
             if(need1->parent != nullptr){
                if(need1->word<need1->parent->word){
                    need1->parent->left=need1;
                }else{
                 need1->parent->right=need1;}}
         need1->right=need2;
         need2->parent=need1;
         if(need1!=q->left){
         need1->left=q->left;
             q->left->parent=need1;
             if(q==root){root=need1; delete q; return;}
             else{ delete q; return; }
         } else{
             need1->left = nullptr;
            }
         }
         else{
             need1->parent=q->parent;
             need1->right=need2;
             need2->parent=need1;
             if(need1->parent == nullptr){
                 delete q;
                 root=need1;
                 return;
             }
             if(q->word<q->parent->word) q->parent->left=need1;
             else q->parent->right=need1;
             delete q;
        }
     }
 }

 friend ostream & operator << (ostream &out, const lexicon &l){
        node *q=l.root;
         if(q!=nullptr){
             print_aux(q->left,out);
             out<<q->word<<" "<<q->times<<endl;
             print_aux(q->right,out);
         }
    return out;
 }




private:
    struct node{
        int times;
        string word;
        node *left,*right,*parent;
        node(const string &x,const int &t, node *l, node *r, node *p)
            : word(x),times(t),left(l), right(r), parent(p) {}
    };
    node *root;
    node *place(const string &s){
        node *current = root;
        while(current != nullptr && current->word != s) {
            if (current->word < s)current = current->right;
            else current = current->left;
        }
        return current;
    }
    static void purge(node *t) {
        if (t != nullptr) {
            purge(t->left);
            purge(t->right);
            delete t;
        }
    }
    static void print_aux(node *t,ostream &out){
        if(t!=nullptr){
            print_aux(t->left,out);
            out<<t->word<<" "<<t->times<<endl;
            print_aux(t->right,out);
        }
    }
    node *insert_aux(node *t,const string &word){
        if(t==nullptr){
            node *p = new node(word,1,nullptr, nullptr, nullptr);
            return p;
        }
        if(t->word>word){
        t->left = insert_aux(t->left,word);
        t->left->parent=t;
        } else if(t->word<word){
        t->right=insert_aux(t->right,word);
        t->right->parent=t;
        } else if(t->word==word) t->times+=1;
        return t;
    }

    node *search(node *t){
        node *q=t;
        while(q->right != nullptr) q=q->right;
        if(q!=t){
        if(q->left != nullptr) {
            q->parent->right = q->left;
            q->left->parent = q->parent;
            q->left = nullptr;
        }
        }
        return q;
    }
};
