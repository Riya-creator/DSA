class Solution {
    //s1, s2 ->> 2 partitiong of array 
    //s1+s2= sum 
    //s1- s2 = target
    //tranform the problem from making sum to be target ->exponential -->
    //finding the value of s2 (smaller in size then s1 seen by equation) then find the subset sum as s2 that is total number of ways to cover  
    int solve(vector<int>&nums,vector<vector<int>>&dp, int target, int i){
        if (i == nums.size() - 1) {
    int ways = 0;

    if (target == 0) ways++;          // notTake
    if (nums[i] == target) ways++;   // take

    return ways;
}
        if( dp[i][target]!= -1) return dp[i][target];
//here we took vector as here we hv to take all positive only(SUBSET SUM)
        int take=0 , not_take= solve(nums, dp, target, i+1);
        if(nums[i]<= target) take= solve(nums, dp, target-nums[i], i+1);
        return dp[i][target]= take +not_take;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum=0;
        for( int s:  nums) sum+=s;
        if( sum-target<0 || (sum-target )%2 ==1) return 0;
        int s2= (sum-target)/2;
        vector<vector<int>>dp(nums.size(), vector<int>(s2+1,-1));
        return solve(nums, dp, s2, 0 );
    }
};

//also note: if 0 then double the ans so even on sum== target we don't proceed with 1 as ans
