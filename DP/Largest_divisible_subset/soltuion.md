class Solution {
public:
//time:O(n2)
//space:O(n)
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<int> dp(n, 1);//max length made by this element
        vector<int> parent(n, -1);//last divisible by
        int maxLen = 1;
        int last = 0;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]){//if better deal then go 

                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
            if(dp[i] > maxLen){
                maxLen = dp[i];
                last = i;//track the max array 
            }
        }
        vector<int> ans;
        while (last != -1) {
            ans.push_back(nums[last]);
            last = parent[last];
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};
