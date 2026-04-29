int countSubsets(vector<int>& arr, int target) {
    int n = arr.size();
    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));

    // base case
    dp[0][0] = 1; // 1 way: empty subset

    for (int i = 1; i <= n; i++) {
        for (int sum = 0; sum <= target; sum++) {
            // NOT TAKE
            dp[i][sum] = dp[i-1][sum];

            // TAKE
            if (arr[i-1] <= sum) {
                dp[i][sum] += dp[i-1][sum - arr[i-1]];
            }
        }
    }

    return dp[n][target];
}
//also covers double count on 0 element in the array
