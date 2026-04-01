class Solution {
    // states: 1. holding/released 2. index for the price
    /* transitions:{
        1. holding([..][1])--> then release or do nothing
        2. not holding ([..][0])  ->>then buy or do nothing
     }
     */
public:
//dp[i][0/1]== max profit at index at both 0/1
    int maxProfit(vector<int>& prices) {
        vector<vector<int>>dp( prices.size(), vector<int>(2, 0));
//BASE case 
        dp[0][0]=0;//not holding at start then 0
        dp[0][1]=-prices[0];//buy the first stock then negative
        for( int i=1; i< prices.size(); i++){
            dp[i][0]= max(dp[i-1][0], dp[i-1][1]+prices[i] );
            dp[i][1]= max(dp[i-1][1], dp[i-1][0]- prices[i]);
        }
        return dp[prices.size()-1][0];//at end need to sell all the stocks
    }
};
