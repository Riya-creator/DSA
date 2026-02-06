#include <iostream>
using namespace std;
class tnode{
    public:
    int val;
    tnode *left= NULL;
    tnode *right= NULL;
    tnode( int c){
        val= c;
    }
};
class tree{
    public:
    tnode *root=NULL;
    //ques 2 iterative
    bool search(int v){
        if( root== NULL) return false;
        if( root->val == v) return true;
        tnode * temp= root;
        while(temp){
            if( temp->val == v) return true;
            if( temp->val>v) temp= temp->left;
            else temp= temp->right;
        }
        return false;
    }
    tnode *maxi(){
        if(root==NULL) return root;
        tnode *t=root;
        while(t->right){
            t=t->right;
        }
        return t;
    }
    tnode * mini(){
        if(root==NULL) return root;
        tnode *t=root;
        while(t->left){
            t=t->left;
        }
        return t;
    }
//ques2 d
tnode * prede(tnode * root, int v, tnode *prev){
    if( root== NULL) return NULL;
    tnode * l =prede (root->left, v, prev);
    if( l) return l;
     
    if( root->val == v) return prev;
    else {
        prev= root;
    }
    tnode *  r= prede(root->right, v,prev);
    return r;
}
//q2 e
tnode * succ(tnode * root, int v, int &found){
    if( root== NULL) return NULL;
    tnode * l =succ (root->left, v, found);
    if( l) return l;
    if( found == 1) return root;
    if( root->val == v) found =1;
    
    tnode *  r= succ(root->right, v, found);
    return r;
}
};
//ques2 a rec
bool search( tnode *r, int v){
    if( r== NULL) return false;
    if( r->val == v) return true;
    if( r->val >v)
     return search(r->left , v);
    else return search( r->right, v);
}
    tnode* insert(int v, tnode *root){
        if(root==NULL) {
            root= new tnode(v);
            return root;
        }
        if(root->val== v) return root;
        if(root->val >v)
        root->left= insert(v, root->left);
        else root->right= insert(v, root->right);
        return root;
    }
    void show(tnode *r ){
        if(r ==NULL) {
            return;
        }
        tnode *t= r;
        show(r->left);
        cout<<t->val<<endl;
        show(r->right);
    }
int main()
{
    tree t;
    t.root =insert(4,t.root);
    insert(5,t.root);
    insert(7,t.root);
    insert(2,t.root);
    insert(4, t.root);
    show(t.root);
    cout<<"\n so Let's see if the node exist :"<<search(t.root, 0 )<<t.search(0);
    tnode * a = t.prede(t.root, 7,NULL);
    if( a)
    cout<<"\nLet's see the predesessor..: "<< a->val;
    else cout<<"\nNo predesessor exist";
    int found =0;
    tnode * b = t.succ(t.root, 2,found);
    if( b)
    
    cout<<"\nLet's see the successor..: "<< b->val;
    else cout<<"\nNo successor exist\n";
    tnode * h= t.maxi();
    if(h) cout<<"\nmaximum is:"<<h->val<<endl;
    else cout<<"\nNo maximum";
    tnode * g= t.mini();
    if(g) cout<<"\nmaximum is:"<<g->val<<endl;
    else cout<<"\nNo maximum";
}
