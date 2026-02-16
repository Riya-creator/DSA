class Solution {
    void backtrack(vector<int>&nums, vector<vector<int>>&ans,vector<int>&cur,int mask){
        if(cur.size()==nums.size()){
            ans.push_back(cur);
            return ;
        }
        for(int i=0; i<nums.size(); i++){
            if((mask & (1<<i))==0) {
                //if ith bit is not checked in the iteration
                cur.push_back(nums[i]);//take it

                backtrack(nums,ans, cur, mask |(1<<i));//explore
                cur.pop_back();//undo choicek
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>ans;
        vector<int>cur;
        backtrack(nums, ans, cur, 0);
        return ans;
    }
};
//time: O(n! *n)
//space: O(N! *N)
