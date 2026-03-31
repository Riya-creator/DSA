//EDGE CASE:: sum-target >0 not sum>target why?
//-->>beacause target can be negative here then sum+target will be +ve
//all have DIFF CONCEPTS Must try all of them 
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum =0;
        for( int n: nums) sum+= n;
        if( sum-target <0 || (sum - target)%2 != 0) return 0;

        int s2=  (sum - target)/2 ;
        vector<vector<int>>dp(nums.size()+1, vector<int>(s2+1, 0));
        //must be 0 only as tabulation need to add them which need 0 not -1
        for(int i=0; i<nums.size()+1;i++){
            dp[i][0]=1;
        }
        
        for(int  i=1; i< nums.size()+1; i ++){
            for (int j=0; j<s2+1; j++ ){
                dp[i][j]= dp[i-1][j];//not take

                if( nums[i-1] <=j){
//taken then addition if rest amount is coverd too
                    dp[i][j] += dp[i-1][j- nums[i-1]] ;
                }
            }
        }
        return dp[nums.size()][s2];
    }
};
//space n time: O(n*k)  (k=s2)
