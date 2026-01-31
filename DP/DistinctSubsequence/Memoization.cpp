//dp representation:number of ways using s[i:] to build t[j:]
class Solution {
    int solve(string &s, string &t, int s1, int t1, vector<vector<long long>>&dp){
        if(t1>= t.size()){
            return 1;
        }//need to checked first only as completed 
        if(s1>=s.size()) return 0;
        if(dp[s1][t1]!=-1) {
            return dp[s1][t1];
        }
        long long x=solve(s ,t, s1+1,t1, dp), y=0;
        if(s[s1]==t[t1]) y=solve(s,t, s1+1, t1+1 ,dp);
        return dp[s1][t1]=x+y;
    }
public:
    int numDistinct(string s, string t) {
        vector<vector<long long>>dp(s.size()+1, vector<long long>(t.size()+1, -1));
        //remember dp always n+1 here it work without that tooo as return before the access of the dp
        return solve(s, t, 0, 0, dp);
    }
};
