class Solution {
public:
//dfs+memo
    int  dfs(vector<vector<int>>& adj, vector<int>&quiet, vector<int> &dp, int i){
        if(dp[i]!= -1) return dp[i];
        
        dp[i]= i;//assuming itself as best

        for(auto v: adj[i]){
            int possible= dfs(adj, quiet, dp, v);

            if(quiet[dp[i]] > quiet[possible]){
                dp[i]= possible;    
            }
        }
        
        return dp[i];
    }
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>>adj(n);
        for( auto &a: richer){
//reverse of richer edges are stored as then only direct look at more richer ones
            adj[a[1]].push_back(a[0]);
        }

        vector<int> dp(n, -1);
        for( int i=0; i< n; i++){
            dp[i] = dfs(adj, quiet, dp, i);
        }
        return dp;
    }
};
