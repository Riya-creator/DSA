class Solution {
    void backtrack(vector<int>&nums, vector<vector<int>>&ans,vector<int>&cur,vector<bool>&used){
        if(cur.size()==nums.size()){
            ans.push_back(cur);
            return ;
        }
        for(int i=0; i<nums.size(); i++){
            if(used[i]) continue;
            used[i]=true;
            //lock it
            cur.push_back(nums[i]);//take it

            backtrack(nums,ans, cur, used);//explore
            cur.pop_back();//undo choice
            used[i]=false;//unlock to avoid deadlock
        }
        return ;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>ans;
        vector<int>cur;
        vector<bool> used(nums.size(),false);
        backtrack(nums, ans, cur, used);
        return ans;
    }
};
