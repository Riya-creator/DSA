class Solution {
    //making 2d dp or do is overkill for this
public:
    int lengthOfLIS(vector<int>& nums) {
        //dp[i]=max length of increasing subsequence ending at index i
        //make each subsequence n check acc
        vector<int>dp(nums.size(), 1);
        int ans=1;
        for( int i=1; i< nums.size();i++){
            for( int j=i-1;j>=0; j--){
                if(nums[i]>nums[j]){
                    dp[i]= max({dp[j]+1,dp[i]});
                }
            }
                ans=max(ans,dp[i]);
        }
        return ans;
    }
};
