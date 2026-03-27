class Solution {
    int solve( string& s, int i, int j, vector<vector<int>>&dp){
        if( i<0 && j>= s.size()) return 0;
        if( i<0 || i>= s.size() )
        return s.size()-j;
        if(j<0 || j>= s.size()) return i+1;
        if( dp[i][j]!= -1) return dp[i][j];
        if( s[i]== s[j] ) return dp[i][j]= solve( s, i-1, j+1 ,dp);
        return dp[i][j]= 1+min(solve(s, i+1, j, dp), solve(s, i, j+1, dp));
    }
public:
    int minInsertions(string s) {
        int ans= INT_MAX;
        vector<vector<int>>dp(s.size(), vector<int>(s.size(), -1));
        for( int i=0; i< s.size(); i++){
            ans = min(ans, solve(s, i, i, dp));
            if(i+1<s.size()-1 && s[i]== s[i+1])
            ans= min( ans, solve(s, i, i+1, dp));
        }
        return ans;
    }
};
/*
expanding out method (WRONG):
*assume center of 1 or 2 characters of the strings 
*then handling the mismatch from there on while expanding 
**BUT CENTER WILL CHANGE WITH EVERY INSERTION MAKING THE BASE OF THE OPERATION TO BE SHATTERED

**followed a LOCAL Approach to :
"Fix around a center"
**instead u want:
"Fix the Entire string globally"

“I tried center expansion but realized it fails because insertions can alter global symmetry beyond fixed centers”
*/
