class Solution {
    //time :O(n3) space :O(n2)
    // interval dp
public:
    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());
        int le = cuts.size();
        vector<vector<int>>dp(le+2, vector<int>(le+2, 1e9));
        //as we inc the leng for the array by 2 then indexx for these need to be inc 

        vector<int>a(le+2, 0);
        a[le+1] = n; 
        for( int i=0; i< le; i++){
            a[i+1] = cuts[i];
        }

        for( int i=0; i< le+1; i++){
            dp[i][i+1] = 0;
            //making adjacent index cost as 0
            //no cuts possible between them as no space
            //IMP: for base case approving
        }

//dp[l][r] = min cost for covering the cuts in a[l] and a[r] 
        for( int len = 2; len<= le+1 ; len++){

            for(int l= 0; l+ len<= le+1 ; l++){

                int r= l+len;
//we leave the l n r for making the physical boundaries
                for( int k=l+1 ; k<r ; k++){
                    int  L = a[l], R= a[r];
                    int check  = dp[l][k] + dp[k][r] + (R-L)  ;

                    dp[l][r] = min(dp[l][r], check);
                }
            }
        }
        return dp[0][le+1];
    }
};
