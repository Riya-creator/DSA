class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        std::vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            int maxGain = INT_MIN;
            int currentSum = 0;

            for (int x = 1; x <= 3 && i + x <= n; ++x) {
                currentSum += stoneValue[i + x - 1];
                maxGain = std::max(maxGain, currentSum - dp[i + x]);
            }

            dp[i] = maxGain;
        }

        if (dp[0] > 0) return "Alice";
        if (dp[0] < 0) return "Bob";
        return "Tie";
    }
};
