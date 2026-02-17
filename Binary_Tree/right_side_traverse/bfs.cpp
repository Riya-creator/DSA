class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(root== NULL)
        return ans;
        queue<TreeNode * > q;
        q.push(root);
        while( !q.empty()){
            int n= q.size();
            for(int i=1; i<=n; i++){
                TreeNode *nn= q.front();
                if( i==n)
                ans.push_back(nn->val);
                if( nn->left!= NULL)
                q.push(nn->left);
                if(nn->right!= NULL)
                q.push(nn->right);
                q.pop();
            }
        }
        return ans;
    }
};
//time:O(N) sapce : O(N)
