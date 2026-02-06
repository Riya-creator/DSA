class Solution {
    void ind(vector<int>&in, TreeNode * root){
        if( root== NULL) return ;
        ind(in, root->left);
        in.push_back(root->val);
        ind(in, root->right);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> inorder;
        ind(inorder, root);
        int l= 0, r= inorder.size()-1, sum=0;
        while(l<r){
            sum= inorder[r] +inorder[l];
            if( sum==k ) return true;
            if( sum> k) r--;
            else l++;
        }
        return false;
    }
};
