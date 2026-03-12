//basically all 3 forms of dp solution is same logic just the way for representation is changing
class Solution {
public:
    int rob(vector<int>& nums) {
        if( nums.size()==1) return nums[0];
        int prev2= 0, prev1=nums[0], curr;
        for(int i=1; i< nums.size(); i++){
            curr = max(nums[i]+prev2, prev1);
            // including, excluding max taken
            prev2= prev1;
            prev1= curr;
        }
        return  prev1;
    }
};
// time: O(n)
// space: O(1)
