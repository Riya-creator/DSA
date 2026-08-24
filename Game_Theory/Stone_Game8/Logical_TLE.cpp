class Solution {
    //max diff from both aspect 
    //curr_player-opponent_player
    int game (vector<long long>&prefix, int i, vector<long long>& dp ){
        if(i> prefix.size() -1 ) return 0;
        if( dp[i] != LLONG_MIN) return dp[i];

        long long  ans = LLONG_MIN;
        for( int j=i; j<prefix.size(); j++){
            ans = max( ans, prefix[j] - game(prefix, j+1, dp));
        }

        return dp[i] = ans;
    }
public:
    int stoneGameVIII(vector<int>& stones) {
        vector<long long>prefix(stones.size(), stones[0]);
        vector<long long>dp(stones.size(),LLONG_MIN );

        for( int i=1; i<stones.size(); i++){
            prefix[i] = stones[i] +prefix[i-1];
        }

        return game(prefix, 1 ,dp );
    }
};
