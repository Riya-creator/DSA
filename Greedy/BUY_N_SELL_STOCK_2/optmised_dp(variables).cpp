class Solution {
    //optimsied dp==>>>1 d variables 
    // time:O(n)  & space= O(1)
public:
    int maxProfit(vector<int>& prices) {
        int nothold=0, hold= -prices[0];

        for(int i=1; i<prices.size(); i++){
            int prevnot_hold= nothold;

            hold= max(hold, prevnot_hold-prices[i]);//skip or buy
            nothold= max(nothold, hold+ prices[i]);//skip or sell
        }
        return nothold;
    }
};
