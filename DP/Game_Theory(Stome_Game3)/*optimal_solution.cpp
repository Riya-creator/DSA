class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
    // time:o(n) space O(1)
    //space optimised 
    //from top-to bottom -->to bottom up as
    //recusion overhead make memory fill up

        int n = stoneValue.size();
        int dp1 = 0, dp2 = 0, dp3 = 0; // Represents dp[i+1], dp[i+2], dp[i+3]

        for (int i = n - 1; i >= 0; --i) {
            int maxGain = INT_MIN;
            int currentSum = 0;

            if (i + 1 <= n) {
                currentSum += stoneValue[i];
                maxGain = std::max(maxGain, currentSum - dp1);
            }
            if (i + 2 <= n) {
                currentSum += stoneValue[i + 1];
                maxGain = std::max(maxGain, currentSum - dp2);
            }
            if (i + 3 <= n) {
                currentSum += stoneValue[i + 2];
                maxGain = std::max(maxGain, currentSum - dp3);
            }

            dp3 = dp2;
            dp2 = dp1;
            dp1 = maxGain;
        }

        if (dp1 > 0) return "Alice";
        if (dp1 < 0) return "Bob";
        return "Tie";
    }
};
