class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy1=INT_MAX, buy2= INT_MAX , sell1= 0, sell2= 0;
        for (int p : prices){
            buy1 = min(buy1, p );
            sell1= max(sell1, p- buy1);

            buy2 = min(buy2, p- sell1);
            sell2= max(sell2, p- buy2);
        }
        return sell2;
    }
};
//leetcode 123 best time to buy n sell 3
//both buy are made in continuation of the sum or total amount that's why that makes this to optimal solutino for this
