//this is basically making the inordere traversal of bst using the node traversal
//as right one is coming form the descending order from the largest -> smallest n the left is vice n versa
class Solution {
    void pushl( TreeNode * r, stack<TreeNode*> &l){
        while(r){
            l.push(r);
            r= r->left;
        }
    }
    void pushr( TreeNode * root, stack<TreeNode*> &r){
        while(root){
            r.push(root);
            root= root->right;
        }
    }
public:
    bool findTarget(TreeNode* root, int k) {
        stack<TreeNode *> l,r ;
        pushl(root, l);
        pushr(root, r);
        TreeNode * temp;
        while( !l.empty() && !r.empty() && l.top()!= r.top()){
            int sum= l.top()->val+ r.top()->val;
            if( sum== k) return true;
            if( sum< k){
                temp= l.top();
                l.pop();
                pushl(temp->right, l);
            }
            else{
                temp= r.top();
                r.pop();
                pushr(temp->left, r);
            }
        }
        return false;
    }
};
