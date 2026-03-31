class Solution {
    int solve (vector<int> &nums, int target , int index, map<pair<int, int>, int>&dp, int sum){
        
        if( dp.count({index, sum}) != 0) return dp[{index, sum}];
        if( index == nums.size()-1) {
            int ans=0;
            if( sum+ nums[index] == target) ans++;
            if( sum - nums[index] == target ) ans ++;
            return dp[{index, sum}]= ans;  
        }
        int x= solve(nums, target, index+1, dp, sum+ nums[index]), y= solve(nums, target, index+1, dp, sum-nums[index]);
        return dp[{index, sum}]= x+y;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        map<pair<int, int>, int>dp;
        //index, current_sum -->> number of after that possible to make the taget
        //preferred map here as there can be negative sum as well
        return solve(nums, target , 0, dp, 0);
    }
};
