class Solution {
    //o(n2)
    int dp[21][21]; //at alternative call we have the current player at goal to win
    //by: me- opponent_advantage
    //dp storers advntage current player had over another
    
    int solve(vector<int>&nums, int i, int j){
        if(i==j) return nums[i];
        if(dp[i][j]!=-1) return dp[i][j];

        int right= nums[j]- solve(nums, i, j-1);
        int left= nums[i] - solve(nums, i+1, j);

        return dp[i][j]= max(right, left);
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));// used to set each byte of integer
//return ans only as state of dp says that it returnns the adv of the current player n the current or the first is player one only
        return solve(nums,0, nums.size()-1)>=0;
    }
};
