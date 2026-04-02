// leetcode : 188 
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if( k>= prices.size()/2){
            int profit=0;
            for( int i=1; i< prices.size(); i++){
                if( prices[i]> prices[i-1])
                profit += (prices[i]- prices[i-1]);
            }
            return profit;
        }
        vector<vector<vector<int>>>dp(prices.size(), vector<vector<int>>(k+1, vector<int>(2, 0)));

        for ( int i=0; i<= k; i++){
            dp[0][i][0]= 0;
            dp[0][i][1] =  -prices[0];
        }
        for( int i=1; i<prices.size(); i++){
            for( int j=1; j<= k; j++ ){
                dp[i][j][0]= max( dp[i-1][j][0], dp[i-1][j][1]+prices[i]);
                dp[i][j][1]= max(dp[i-1][j][1], dp[i-1][j-1][0]-prices[i]);
            }
        }
        return dp[prices.size()-1][k][0];
    }
};
