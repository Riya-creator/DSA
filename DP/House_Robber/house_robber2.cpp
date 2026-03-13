//here the robber have the houses in circular form i mean that if 1st is taken then last is not n vice a versa

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        
        return max(linear_rob(nums, 0, nums.size() - 2), 
                   linear_rob(nums, 1, nums.size() - 1));
    }

private:
    int linear_rob(vector<int>& nums, int start, int end) {
        int rob1 = 0, rob2 = 0;
        
        for (int i = start; i <= end; i++) {
            int temp = max(rob1 + nums[i], rob2);
            rob1 = rob2;
            rob2 = temp;
        }
        return rob2;
    }
};
