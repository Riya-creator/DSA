class Solution {
    //brute force --> very heavy dp made from this
    bool predict(vector<int> &nums, int start, int end, int p1, int p2, bool turn ){
        if( start >end) return p1>= p2;

        if( turn){
            bool left= predict(nums, start+1, end, p1+nums[start], p2, false);
            bool right = predict(nums, start , end-1, p1+nums[end], p2, false);
            return left || right; // add as p1 wins for true
        }else{
            bool left= predict(nums, start+1, end, p1, p2+nums[start], true);
            bool right = predict(nums, start , end-1, p1, p2+nums[end], true);
            return left && right; //and operation
        }
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        return predict(nums, 0, nums.size()-1, 0, 0, true);
    }
};
/*time: O(2^n)

Imagine

n = 20

Maximum sum = 200

DP becomes

dp[20][20][201][201][2]*/
