//work oon the last ballon to burst rather then first
//time:O(n3) , space:O(n2)
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> a(n + 2, 1);

        for (int i = 0; i < n; i++) {
            a[i + 1] = nums[i];// adding this: last element have numbers rather than handle explicitly
        }

        //dp[l][r] = max coins by deleting all stricly inside l,r
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

//min length pair to find removal case:2 
// ordere maintained :  l< k<r nothing got same as
// we alwayss pick the ending elements at last as they don't have anythin one side so min profit from them so used for all in between elements then cover the ending elements at last

        for (int len = 2; len < n + 2; len++) {

            for (int l = 0; l + len < n + 2; l++) {
                int r = l + len;
                // k-> last ballon to burst
                for (int k = l + 1; k < r; k++) {
                    int coins =dp[l][k] +dp[k][r] +a[l] * a[k] * a[r];
//burst everything left + everything right of k then finally burst k

                    dp[l][r] = max(dp[l][r], coins);
                    //to try everyy possible ballon then keep the best
                }
            }
        }
        //intervals smaller are covered first then used in furthure everything case

        return dp[0][n + 1];
    }
};
