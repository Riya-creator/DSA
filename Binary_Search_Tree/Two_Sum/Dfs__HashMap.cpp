class Solution {
    void dfs( TreeNode * root, unordered_map<int, int>&mp){
        if(root== NULL) return ;
        mp[root->val] ++;
        dfs(root->left, mp);
        dfs(root->right, mp);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_map<int, int>mp;
        dfs(root, mp);
        for(auto m:mp){
            if( k-m.first == m.first){
                if(mp.count(k-m.first)==2) return true;
                else continue;
            } 
            if( mp.count(k-m.first)) return true;
        }
        return false;
    }
};
