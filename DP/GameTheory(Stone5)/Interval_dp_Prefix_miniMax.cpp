class Solution {
// space:: O(n2) --> recusion n prefix O(n), dp O(n2) , 
// time O(n^3) ==>> O(n2) possible interval state * O(n) pssible partitions
    int solve(vector<int>&prefix, int s, int e, vector<vector<int>>&dp,int prev){
        if(s>=e) return 0;

        if(dp[s][e]!= -1) return dp[s][e];

        int ans =0;
        for(int i=s ; i<e ; i++){
            int diff1 , diff2 = prefix[e]-prefix[i];
          //diff is the subarray sum

            if(prev !=-1 ) diff1= prefix[i]-prefix[prev] ;
            else diff1= prefix[i];

            if(diff1 == diff2){
                
                diff2 += solve(prefix, i+1, e, dp, i);
                diff1 += solve(prefix, s, i, dp, prev);

                if(diff1 >ans){
                    ans = diff1;
                }
                if(diff2>ans ){
                    ans= diff2;
                }
            }else if( diff1 > diff2 ){

                int out =diff2 + solve(prefix, i+1, e, dp, i);

                if(out>ans) {
                    ans = out;
                }

            }else{
                int out  = diff1 + solve(prefix, s, i, dp, prev);

                if(ans<out){
                    ans = out;
                }
            }
        }

        return dp[s][e] = ans;            
    }
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n= stoneValue.size();
        vector<int>prefix(n);

        prefix[0]= stoneValue[0];
        for(int i=1 ;i <n ;i ++){
            prefix[i] = prefix[i-1] +stoneValue[i];
        }
//dp:: define the current state properly
//dp[i][j]:: s n end of interval
//as prev also define the diff in sum in prefix
        vector<vector<int>>dp(n, vector<int>(n, -1));

        return solve(prefix, 0, n-1, dp, -1);
    }
};
