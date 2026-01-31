class Solution {
public:
    int numDistinct(string s, string t) {
        vector<unsigned long long> dp(t.size()+1, 0), dummy(t.size()+1, 0);
        dp[t.size()]=1;
        for( int i=s.size()-1; i>=0; i--){
            dummy =dp;
            for(int j=t.size()-1; j>=0; j--){
                if(s[i]==t[j]){
                    dp[j]= dummy[j+1]+ dummy[j];
                }else dp[j]= dummy[j];
            }
        }
        return (int)dp[0];
    }
};
