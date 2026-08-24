class Solution {
//time n space: O(n)
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        vector<long long> prefix(n);

        prefix[0] = stones[0];
        for(int i = 1; i < n; i++)
            prefix[i] = prefix[i-1] + stones[i];

        long long ans = prefix[n-1];
//instead of tracing the max from ind j we took ans as max as only matter is future best solution only

        for(int i = n-2; i >= 1; i--)
            ans = max(ans, prefix[i] - ans);

        return ans;
    }
};
