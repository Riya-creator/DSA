class Solution {
    //same idea  but optimised approach
    //time:O(k × 2^k)
    //space:O(2^k)
public:
    vector<pair<int,int>> src, dest;
    int dp[1<<8];

    int solve(int mask) {
        int k = __builtin_popcount(mask);
        if(k == dest.size()) return 0;//count of how much is done n 0 based index so used as next index
        //set bit in mask::
        //count== number of src use
        //position == des index used

        if(dp[mask] != -1) return dp[mask];

        int ans = 1e9;

        for(int j = 0; j < dest.size(); j++) {
            if(mask & (1<<j)) continue;

            int d = abs(src[k].first - dest[j].first)
                  + abs(src[k].second - dest[j].second);

            ans = min(ans, d + solve(mask | (1<<j)));
        }

        return dp[mask] = ans;
    }

    int minimumMoves(vector<vector<int>>& grid) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(grid[i][j] == 0)
                    dest.push_back({i,j});

                for(int k = 1; k < grid[i][j]; k++)
                    src.push_back({i,j});
            }
        }

        memset(dp, -1, sizeof(dp));
        return solve(0);
    }
};
