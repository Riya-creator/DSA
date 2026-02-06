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
    //Iteration Q3
    int maxdep(tnode *root){
        if(root == NULL) return 0;
        int x=maxdep(root->left);
        int y= maxdep(root->right);
        return max(x,y)+1;
    }
    int mindep(tnode *root){
        if(root == NULL) return 0;
        int x=mindep(root->left);
        int y= mindep(root->right);
        return min(x,y)+1;
    }
    // void insert(int v){
    //     tnode *nn = new tnode (v);
    //     if( root== NULL) {
    //         root =nn;
    //         return;
    //     }
    //     tnode *temp= root;
    //     while( temp ){
    //         if( temp->val == v) return;
    //         if( temp->val < v){
    //             if( temp->right == NULL){
    //                 temp->right= nn;
    //                 return;
    //             }
    //             else temp = temp->right;
    //         } 
    //         if( temp->val >v ){
    //             if( temp->left == NULL){
    //                 temp->left= nn;
    //                 return;
    //             }
    //             else temp = temp ->left;
    //         }
    //     }
    // }
    
};
//Ques4
class Solution {
    tnode * prev=NULL;
    bool make(tnode * root ){
        if( root== NULL) return true;
        bool y= make( root->left);

        if(prev && root->val <= prev->val)
        return false;
        prev= root;

        bool n= make(root->right);
        return n && y;
    }
    public:
        bool isValidBST(tnode* root) {
            return make(root);
        }
};
//Ques1
    //preorder
    void pre(tnode *root){
        if(!root) return ;
        cout<<root->val;
        pre(root->left);
        pre(root->right);
    }
    //postorder
    void post(tnode *root){
        if(!root) return ;
        post(root->left);
        post(root->right);
        cout<<root->val;
    }
    //inorder
    void in(tnode *root){
        if(root==NULL) return;
        in(root->left);
        cout<<root->val;
        in(root->right);
    }
    //next variant
    //recursive
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
        cout<<t->val;
        show(r->right);
    }
int main()
{
    tree t;
    
    // t.insert(4);
    // t.insert(5);
    // t.insert(7);
    // t.insert(2);
    // t.insert(4);
    
    //rec
    t.root =insert(4,t.root);
insert(5,t.root);
    insert(7,t.root);
    insert(2,t.root);
    insert(4, t.root);
    show(t.root);
    Solution s;
    cout<<endl<<s.isValidBST(t.root);
}
