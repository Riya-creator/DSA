class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size()==1) return nums[0];
        //base case n=1
        vector<int>dp(nums.size());
        dp[0]= nums[0];
        dp[1]= max(nums[0], nums[1]);//base case n=2
        for( int i=2; i< nums.size(); i++){
            dp[i]= max(dp[i-1], dp[i-2]+nums[i]);
        }
        return dp[nums.size()-1];
    }
};
//time n space: O(n)
