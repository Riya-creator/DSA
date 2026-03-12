class Solution {
    int solve(int i, vector<int>& nums, vector<int>& dp){
        
        if(i >= nums.size())
            return 0;

        if(dp[i] != -1)
            return dp[i];

        int rob = nums[i] + solve(i+2, nums, dp);
        int skip = solve(i+1, nums, dp);

        return dp[i] = max(rob, skip);
    }

public:
    int rob(vector<int>& nums) {
        
        vector<int> dp(nums.size(), -1);
        return solve(0, nums, dp);
    }
};
//generating all the subsequence by picking or leaving
//time: O( n)
// space: O(n+n) : recursion n the array
