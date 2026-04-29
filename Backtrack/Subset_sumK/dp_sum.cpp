    #include <bits/stdc++.h> 
    //make recursive subset then check for that by mask
    bool subsetSumToK(int n, int k, vector<int> &arr) {
        //dp sum
        vector<vector<bool>>dp(n+1,vector<bool>(k+1,false));

        for(int i=0; i<n+1; i++){
            dp[i][0]= true;
        }
        for(int i=1; i<n+1;i++){
            for( int j=1; j< k+1; j++ ){
                //j-->current sum we are looking for from the array number at the index of the i n below 
                if(arr[i-1] <= j)
                    dp[i][j]= dp[i-1][j] || dp[i-1][j-arr[i-1]];
                //it is like not take or take :: 
                else dp[i][j]= dp[i-1][j];
                //not possible to take then must go with prev result only
            }
        }
        return dp[n][k];
    }
