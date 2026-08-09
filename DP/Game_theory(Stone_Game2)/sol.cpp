class Solution {
    int score( vector<int>& piles, vector<vector<int>>&dp, int m, int ind, vector<int>&suffix) {
        if(ind>= piles.size()) return 0;

        if(dp[ind][m]!=-1) return dp[ind][m];

        int ans = 0, curr=0;

        for( int i=1; i<= 2*m && i+ind-1 <piles.size(); i++){

            curr += piles[i+ind-1];

            ans= max(ans,curr+ suffix[ind+i] -
            score(piles, dp, max(m , i), ind+i,suffix));
            //cuurent_scre + totalremaining - opponent_score
        }

        return dp[ind][m]= ans;
    }
public:
    int stoneGameII(vector<int>& piles) {
        int n= piles.size();
        vector<int> suffix(n+1, piles[n-1]);//total_remaining

        suffix[n] =0;
//* taking last as 0 is part then that means like taking all rest numbers

        for(int i= n-2; i>=0; i--){
            suffix[i] = suffix[i+1] +piles[i];
        }

        vector<vector<int>>dp(piles.size(), vector<int>(2*piles.size(), -1));

        return score(piles, dp, 1, 0, suffix);
    }
};
/*Complexity	
Time	O(n² states) × O(n choices) = O(n³) 
Space	O(n²)
*/
