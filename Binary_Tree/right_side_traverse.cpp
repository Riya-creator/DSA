class Solution {
    void rdfs(TreeNode * root, int level , vector<int>&res){
        if( root== NULL) return;
        if ( level == res.size()) res.push_back(root->val);

        rdfs(root->right, level+1, res);
        rdfs(root->left, level+1, res);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        rdfs( root, 0, res);
        return res;
    }
};
